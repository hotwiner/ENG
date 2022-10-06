#pragma once

#include "entity/components/sprite.h"
#include "entity/components/transform.h"
#include "entity/components/path_finding.h"
#include "grid_map/grid_map.h"
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_stdinc.h>
#include <bitset>
#include <iostream>
#include <map>
#include <memory>
#include <vector>

class EntityManager {
public:
    EntityManager();
    void init();
    void update();
    void addEntity(std::shared_ptr<Entity> entity);
    void deleteEntity(int id);
    void deleteEntity(std::shared_ptr<Entity> entity);
private:
    std::vector<int> freeIDs;
    int setEntityID();
    static std::vector<std::shared_ptr<Entity>> entites;
    int entityID = 0;
};
