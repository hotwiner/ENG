#pragma once

#include "grid_map/grid_map.h"
#include <iostream>

class MapManager {
public:
    MapManager();
    void init();
    void update();

    static std::unique_ptr<CollisionMap> collisionMap;
    static std::unique_ptr<VisualMap> visualMap;
};
