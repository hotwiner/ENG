#include "../include/game/entity_manager.h"
#include <SDL2/SDL_stdinc.h>
#include <SDL2/SDL_surface.h>
#include <memory>
#include <utility>
#include <vector>

std::vector<std::shared_ptr<Entity>> EntityManager::entites;

EntityManager::EntityManager()
{
}

void EntityManager::init()
{
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