#include "../include/game/entity_manager.h"
#include "../include/util/asset_util.h"
#include <SDL2/SDL_stdinc.h>
#include <SDL2/SDL_surface.h>
#include <memory>
#include <utility>
#include <vector>

std::map<const std::string, std::pair<std::shared_ptr<SDL_Texture>, std::shared_ptr<SDL_Surface>>> EntityManager::assetmap;
std::vector<std::shared_ptr<Entity>> EntityManager::entites;
std::unique_ptr<CollisionMap> EntityManager::collmap;

EntityManager::EntityManager()
{
    collmap = std::make_unique<CollisionMap>();
}

void EntityManager::init()
{
    // Initialize all usable asset textures
    EntityManager::assetmap = {
        asset_util::makeAsset("/assests/dog.png"),
        asset_util::makeAsset("/assests/man.gif"),
        asset_util::makeAsset("/assests/man2.gif")
    };

    for (const auto& entity : EntityManager::entites) {
        entity->init();
    }
}

void EntityManager::update()
{
    for (const auto& entity : EntityManager::entites) {
        // std::cout << entity->getPosition().x << " " << entity->getPosition().y << std::endl;
        entity->update();
    }
}

void EntityManager::addEntity(std::shared_ptr<Entity> entity)
{
    entity->id = this->setEntityID();
    EntityManager::entites.push_back(entity);
}

int EntityManager::setEntityID()
{
    if (this->freeIDs.size() > 0) {

        int freeID = *freeIDs.begin();
        this->freeIDs.erase(freeIDs.begin());
        return freeID;
    }

    return this->entityID++;
}

void EntityManager::deleteEntity(int id)
{
    // TODO find and delete entity
    this->freeIDs.push_back(id);
}

void EntityManager::deleteEntity(std::shared_ptr<Entity> entity)
{
    // TODO find and delete entity
    this->freeIDs.push_back(entity->id);
}

//-------------------- COLLISION MAP MOVE TO ANOTHER SOURCE ------------------------

int CollisionMap::gridHeight = 1;
int CollisionMap::gridWidth = 1;

CollisionMap::CollisionMap(int w, int h)
    : width(w)
    , height(h)
{
    auto buff = new std::bitset<10000000UL>;
    map =*buff;
    delete buff;
}

vec2 CollisionMap::toGridPos(vec2 pos)
{
    return {
        std::floor(pos.x / CollisionMap::gridWidth) + 1,
        std::floor(pos.y / CollisionMap::gridHeight) + 1
    };
}

bool CollisionMap::occupyPos(int x, int y)
{
    if (!posOccupied(x, y)) {
        map[(y - 1) * this->width + x] = 1;
        return true;
    }
    return false;
}

bool CollisionMap::occupyPos(vec2 pos)
{
    if (!posOccupied(pos)) {
        map[((int)pos.y - 1) * this->width + (int)pos.x] = 1;
        return true;
    }
    return false;
}

void CollisionMap::unOccupyPos(int x, int y)
{
    map[(y - 1) * this->width + x] = 0;
}

void CollisionMap::unOccupyPos(vec2 pos)
{
    map[((int)pos.y - 1) * this->width + (int)pos.x] = 0;
}

bool CollisionMap::updateOccupancy(vec2 src, vec2 trg)
{
    if (occupyPos(trg)) {
        unOccupyPos(src);
        return true;
    } else {
        occupyPos(src);
    }

    return false;
}

bool CollisionMap::updateOccupancy(int src_x, int src_y, int target_x, int target_y)
{
    if (occupyPos(target_x, target_y)) {
        unOccupyPos(src_x, src_y);
        return true;
    } else {
        occupyPos(src_x, src_y);
    }

    return false;
}

bool CollisionMap::posOccupied(vec2 pos)
{
    if (map[((int)pos.y - 1) * this->width + (int)pos.x] == 1) {
        return true;
    }
    return false;
}

bool CollisionMap::posOccupied(int x, int y)
{
    if (map[(y - 1) * this->width + x] == 1) {
        return true;
    }
    return false;
}

void CollisionMap::reset()
{
    map.reset();
}