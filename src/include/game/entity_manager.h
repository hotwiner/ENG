#pragma once

#include "entity/components/sprite.h"
#include "entity/components/transform.h"

#include <SDL2/SDL_render.h>
#include <SDL2/SDL_stdinc.h>
#include <iostream>
#include <map>
#include <memory>
#include <vector>

class EntityManager {
public:
    void init();
    void update();
    void addEntity(std::shared_ptr<Entity> entity);
    void deleteEntity(int id);
    void deleteEntity(std::shared_ptr<Entity> entity);
    // This includes all useable textures and their surfaces
    static std::map<const std::string, std::pair<std::shared_ptr<SDL_Texture>, std::shared_ptr<SDL_Surface>>> assetmap;

private:
    std::vector<int> freeIDs;
    int setEntityID();
    static std::vector<std::shared_ptr<Entity>> entites;
    int entityID = 0;
};