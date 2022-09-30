#include "../include/game/map_manager.h"
#include <memory>

std::unique_ptr<CollisionMap> MapManager::collisionMap;
std::unique_ptr<VisualMap> MapManager::visualMap;

MapManager::MapManager()
{
    MapManager::collisionMap = std::make_unique<CollisionMap>();
    MapManager::visualMap = std::make_unique<VisualMap>();
}

void MapManager::init()
{
    MapManager::collisionMap->init();
    MapManager::visualMap->init();
}

void MapManager::update()
{
    MapManager::collisionMap->update();
    MapManager::visualMap->update();
}