#include "../../include/game/grid_map/grid_map.h"
#include "../../include/engine/window.h"
#include "../../include/game/asset_manager.h"
#include "../../include/util/sdl_util.h"
#include <cstddef>
#include <iostream>
#include <memory>

int Map::gridWidth = 32;
int Map::gridHeight = 32;
int Map::width = 500;
int Map::height =500;



vec2 Map::toGridPos(vec2 realPos)
{
    return {
        std::floor(realPos.x / Map::gridWidth),
        std::floor(realPos.y / Map::gridHeight)
    };
}

vec2 Map::toRealPos(vec2 gridPos)
{
    return {
        std::floor(gridPos.x * Map::gridWidth),
        std::floor(gridPos.y * Map::gridHeight)
    };
}

std::bitset<250000UL> CollisionMap::map;

CollisionMap::CollisionMap()
{
}

void CollisionMap::init()
{
    auto buff = new std::bitset<250000UL>;
    CollisionMap::map = *buff;
    delete buff;

    for(int i = 0; i < 10; ++i)
    {
        map[Map::width*i +10] = 1;
        if(i < 7)
        map[Map::width*10 +i] = 1;

    }

    for(int i = 0; i < 20; ++i)
    {

        map[Map::width*i +20] = 1;
    }
}

void CollisionMap::update()
{
}

bool CollisionMap::occupyPos(int x, int y)
{
    if (!posOccupied(x, y)) {
        map[(y) * this->width + x] = 1;
        return true;
    }
    return false;
}

bool CollisionMap::occupyPos(vec2 pos)
{
    if (!posOccupied(pos)) {
        map[(pos.y) * this->width + pos.x] = 1;
        return true;
    }
    return false;
}

void CollisionMap::unOccupyPos(int x, int y)
{
    map[(y) * this->width + x] = 0;
}

void CollisionMap::unOccupyPos(vec2 pos)
{
    map[(pos.y) * this->width + pos.x] = 0;
}

bool CollisionMap::updateOccupancy(vec2 grid_src, vec2 trg)
{
    if (occupyPos(trg)) {
        unOccupyPos(grid_src);
        return true;
    } else {
        occupyPos(grid_src);
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
    if (map[(pos.y) * this->width + pos.x] == 1) {
        return true;
    }
    return false;
}

bool CollisionMap::posOccupied(int x, int y)
{
    if (map[(y) * this->width + x] == 1) {
        return true;
    }
    return false;
}

void CollisionMap::reset()
{
    map.reset();
}

VisualMap::VisualMap()
{
}

void VisualMap::init()
{
    createMapTexture();
}

void VisualMap::update()
{
    drawMap();
}

void VisualMap::drawMap()
{
    sdl_util::render_independent(VisualMap::mapTexture.get(), NULL, &this->dest, true);
}

void VisualMap::createMapTexture()
{
    std::shared_ptr<SDL_Surface> mapSurface = sdl_util::make_shared_surface(SDL_CreateRGBSurface(0, width * gridWidth, height * gridHeight, 32, 0, 0, 0, 0));

    SDL_Rect grid_dest;
    SDL_Rect grid_src;

    grid_src.h = Map::gridHeight;
    grid_src.w = Map::gridWidth;
    grid_dest.h = Map::gridHeight;
    grid_dest.w = Map::gridWidth;

    for (int row = 0; row < Map::height; row++) {
        for (int col = 0; col < Map::width; col++) {

            grid_dest.y = row * Map::gridWidth;
            grid_dest.x = col * Map::gridHeight;

            if (CollisionMap::map[row * Map::width + col]) {
                SDL_BlitSurface(AssetManager::assetmap.at("/assests/wall.png").second.get(), NULL, mapSurface.get(), &grid_dest);
            } else {
                SDL_BlitSurface(AssetManager::assetmap.at("/assests/grid.png").second.get(), NULL, mapSurface.get(), &grid_dest);
            }
        }
    }

    this->dest.h = Map::height * Map::gridHeight;
    this->dest.w = Map::width * Map::gridWidth;
    this->dest.x = 0;
    this->dest.y = 0;

    VisualMap::mapTexture = sdl_util::surface_to_texture(mapSurface.get());
    if (mapTexture.get() == nullptr) {
        sdl_util::debug_msg();
    }
}