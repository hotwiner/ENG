#include "../../../include/game/entity/components/path_finding.h"
#include "../../../include/game/entity/components/transform.h"
#include "../../../include/game/grid_map/grid_map.h"
#include "../../../include/game/map_manager.h"
#include <vector>

PathFinding::PathFinding(vec2 realTarget)
    : realTarget(realTarget)
{
    // this->entity->requireComponent<Transform>();
    // std::cout << "has transform" << std::endl;
}

PathFinding::~PathFinding()
{
}

void PathFinding::init()
{
    // findPath();
}
bool one = true;
void PathFinding::update()
{
    if (one) {

        findPath();
        one = false;
    }
}

void PathFinding::setTarget(vec2 realTarget)
{
    this->realTarget = (realTarget);
}

int toGridIndex(vec2 pos)
{
    auto entityGridPos = Map::toGridPos(pos);
    return entityGridPos.y * Map::width + entityGridPos.x;
}

void PathFinding::findPath()
{
    // pair <current tile, tiles until current tile>
    std::vector<int> predecessors;
    std::queue<std::pair<int, std::vector<int>>> pending;
    int currentGridIndex;

    currentGridIndex = toGridIndex(this->entity->getPosition());

    pending.emplace(currentGridIndex, predecessors);

    while (!pending.empty()) {

        auto current = pending.front().first;
        std::vector<int> indexPath = pending.front().second;
        pending.pop();

        // if we reach destination than we have the shortest path
        if (current == toGridIndex(this->realTarget)) {
            for (auto index : indexPath) {

                float gridX = index % Map::width;
                float gridY = (index - gridX) / Map::width;

                this->entity->getComponent<Transform>()->addPathTarget(Map::toRealPos({ gridX, gridY }));
                std::cout << gridX <<  gridY << std::endl;
            }
            break;
        }

        // if not visited move to a neighbor tile
        if (!isVisited(current)) {
            visitedGridIndexes.push_back(current);
            for (auto neigbour : getNeighbours(current)) {
                if(!isVisited(neigbour))
                emplaceNeighbour(indexPath, pending, neigbour);
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

bool PathFinding::isVisited(int gridIndex)
{
    if (std::find(this->visitedGridIndexes.begin(), this->visitedGridIndexes.end(), gridIndex) != this->visitedGridIndexes.end()) {
        return true;
    }
    return false;
}

void PathFinding::emplaceNeighbour(
    std::vector<int>& predecessors,
    std::queue<std::pair<int, std::vector<int>>>& pending,
    int currentGridIndex)
{
    if (!CollisionMap::map[currentGridIndex]) {
        predecessors.push_back(currentGridIndex);
        pending.emplace(std::make_pair(currentGridIndex, predecessors));
    }
}
