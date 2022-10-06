#pragma once

#include "../../../../include/util/vec2.h"
#include "../entity_component.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_stdinc.h>
#include <algorithm>
#include <queue>
#include <vector>

class PathFinding : public Component {
public:
    PathFinding(vec2 realTarget);
    virtual ~PathFinding();
    void init() override;
    void update() override;
    void setTarget(vec2 realTarget); // Saves real position as grid

protected:
    void findPath(); // finds and saves real path positions in transform comp

private:
    vec2 realTarget; // As grid target on collision map
    std::vector<int> getNeighbours(int current); // returns moveable grid neighbours
    std::vector<int> visitedGridIndexes;
    bool isVisited(int gridIndexx);
    void emplaceNeighbour(
        std::vector<int>& predecessors,
        std::queue<std::pair<int, std::vector<int>>>& pending,
        int currentGridIndex);
};
