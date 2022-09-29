#pragma once

#include "entity/components/sprite.h"
#include "entity/components/transform.h"

#include <SDL2/SDL_render.h>
#include <SDL2/SDL_stdinc.h>
#include <bitset>
#include <iostream>
#include <map>
#include <memory>
#include <vector>

class CollisionMap;

class EntityManager {
public:
    EntityManager();
    void init();
    void update();
    void addEntity(std::shared_ptr<Entity> entity);
    void deleteEntity(int id);
    void deleteEntity(std::shared_ptr<Entity> entity);

    // This includes all useable textures and their surfaces
    static std::map<const std::string, std::pair<std::shared_ptr<SDL_Texture>, std::shared_ptr<SDL_Surface>>> assetmap;
    static std::unique_ptr<CollisionMap> collmap;
private:
    std::vector<int> freeIDs;
    int setEntityID();
    static std::vector<std::shared_ptr<Entity>> entites;
    int entityID = 0;
};

class CollisionMap {
    friend class EntityManager;
public:
    CollisionMap(int width=1000, int height=1000);
    bool posOccupied(int x, int y);
    bool occupyPos(int x, int y);
    void unOccupyPos(int x, int y);
    bool updateOccupancy(int src_x, int src_y, int target_x, int target_y);
    void reset();
protected:
    static std::unique_ptr<std::bitset<10000000>> map;
private:
    int width;
    int height;
};