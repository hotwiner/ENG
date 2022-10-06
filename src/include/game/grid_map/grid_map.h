#pragma once

#include "../entity/components/sprite.h"
#include "../entity/components/transform.h"
#include "../entity/entity_component.h"
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_stdinc.h>
#include <bitset>
#include <iostream>
#include <map>
#include <memory>

class Map {
public:
    virtual void init() = 0;
    virtual void update() = 0;

    static vec2 toGridPos(vec2 pos);
    static vec2 toRealPos(vec2 pos);
    static int gridWidth;
    static int gridHeight;
    static int width;
    static int height;
};

class CollisionMap : public Map {
    friend class MapManager;
    friend class VisualMap;
    friend class PathFinding;

public:
    CollisionMap();
    bool posOccupied(int x, int y);
    bool posOccupied(vec2 pos);
    bool occupyPos(int x, int y);
    bool occupyPos(vec2 pos);
    void unOccupyPos(int x, int y);
    void unOccupyPos(vec2 pos);
    bool updateOccupancy(int src_x, int src_y, int target_x, int target_y);
    bool updateOccupancy(vec2 source, vec2 target);
    void reset();

protected:
    void init() override;
    void update() override;

private:
    static std::bitset<250000UL> map;
};

class VisualMap : public Map {
    friend class MapManager;

public:
    VisualMap();

protected:
    void init() override;
    void update() override;
    std::shared_ptr<SDL_Texture> mapTexture;

private:
    SDL_Rect dest;
    void drawMap();
    void createMapTexture();
};