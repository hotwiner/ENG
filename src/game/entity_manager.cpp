#include "../include/game/entity_manager.h"
#include "../include/util/asset_util.h"
#include <SDL2/SDL_stdinc.h>
#include <SDL2/SDL_surface.h>
#include <memory>
#include <utility>

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
    // find and delete entity
    this->freeIDs.push_back(id);
}

void EntityManager::deleteEntity(std::shared_ptr<Entity> entity)
{
    // find and delete entity
    this->freeIDs.push_back(entity->id);
}

std::unique_ptr<std::bitset<10000000>> CollisionMap::map = std::make_unique<std::bitset<10000000>>();

CollisionMap::CollisionMap(int w, int h)
    : width(w)
    , height(h)
{
}

bool CollisionMap::occupyPos(int x, int y)
{
    if (!posOccupied(x, y)) {
        CollisionMap::map.get()[(y - 1) * this->width + x] = 1;
        return true;
    }
    return false;
}

void CollisionMap::unOccupyPos(int x, int y)
{
    CollisionMap::map.get()[(y - 1) * this->width + x] = 0;
}

bool CollisionMap::updateOccupancy(int src_x, int src_y, int target_x, int target_y)
{
    if (occupyPos(target_x, target_y)) {
        unOccupyPos(src_x, src_y);
        return true;
    }

    return false;
}

bool CollisionMap::posOccupied(int x, int y)
{
    if (CollisionMap::map.get()[(y - 1) * this->width + x] == 1) {
        return true;
    }
    return false;
}

void CollisionMap::reset()
{
    CollisionMap::map->reset();
}