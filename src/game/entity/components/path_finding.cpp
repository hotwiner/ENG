#include "../../../include/game/entity/components/path_finding.h"
#include "../../../include/game/entity/components/transform.h"
#include "../../../include/game/grid_map/grid_map.h"
#include "../../../include/game/map_manager.h"
#include <queue>
#include <utility>
#include <vector>

bool PathFinding::newTarget;
vec2 PathFinding::realTarget;

PathFinding::PathFinding(vec2 realTarget)
{
}

PathFinding::~PathFinding()
{
}

void PathFinding::init()
{
    this->entity->requireComponent<Transform>();
}

void PathFinding::update()
{
    if (newTarget) {
        newTarget = false;
        findPath();
    }
}

void PathFinding::setTarget(vec2 realTarget)
{
    PathFinding::realTarget = realTarget;
    newTarget = true;
}

int toGridIndex(vec2 pos)
{
    auto entityGridPos = Map::toGridPos(pos);
    return entityGridPos.y * Map::width + entityGridPos.x;
}

void PathFinding::findPath()
{
    std::queue<vec2> clear;
    std::swap(this->entity->getComponent<Transform>()->path, clear);
    // tuple(state, actions from start to this state)
    std::queue<std::pair<int, std::vector<int>>> que;

    int startIndex = toGridIndex(entity->getPosition());
    int targetIndex = toGridIndex(this->realTarget);
    std::vector<int> indexPath;

    que.push(std::make_pair(startIndex, indexPath));

    std::vector<int> discovered = { startIndex };

    auto is_visited = [&discovered](int index) -> bool {
        if (std::find(discovered.begin(), discovered.end(), index) != discovered.end()) {
            return true;
        }
        return false;
    };

    auto is_obstacle = [](int index) -> bool {
        return CollisionMap::map[index];
    };

    while (!que.empty()) {
        auto frontier = que.front();
        que.pop();

        if (frontier.first == targetIndex) {
            for (auto index : frontier.second) {

                float gridX = index % Map::width;
                float gridY = (index - gridX) / Map::width;

                this->entity->getComponent<Transform>()->addPathTarget(Map::toRealPos({ gridX, gridY }));
            }
            break;
        }

        for (auto& neighbour : getNeighbours(frontier.first)) {
            if (!is_visited(neighbour) && !is_obstacle(neighbour)) {
                discovered.push_back(neighbour);
                frontier.second.push_back(neighbour);
                que.push(std::make_pair(neighbour, frontier.second));
            }
        }
    }
}

// Returns indexes of empty neighbours on collision map
std::vector<int> PathFinding::getNeighbours(int current)
{
    std::vector<int> neighbours;

    if (current + 1 < CollisionMap::map.size())
        neighbours.push_back(current + 1);
    if (current - 1 >= 0)
        neighbours.push_back(current - 1);

    if (current - Map::width >= 0)
        neighbours.push_back(current - Map::width);
    if (current + 1 - Map::width >= 0)
        neighbours.push_back(current + 1 - Map::width);
    if (current - 1 - Map::width >= 0)
        neighbours.push_back(current - 1 - Map::width);

    if (current + Map::width < CollisionMap::map.size())
        neighbours.push_back(current + Map::width);
    if (current + 1 + Map::width < CollisionMap::map.size())
        neighbours.push_back(current + 1 + Map::width);
    if (current - 1 + Map::width < CollisionMap::map.size())
        neighbours.push_back(current - 1 + Map::width);

    return neighbours;
}