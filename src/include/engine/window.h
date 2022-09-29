#pragma once

#include "../util/vec2.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_surface.h>
#include <bits/types/FILE.h>
#include <iostream>
#include <memory>

class Camera;

class Window {
    friend class Camera;
    friend class StateLoop;

public:
    Window(int width = 1920, int height = 1080);

    void clean();
    void render();
    void update();

    static std::shared_ptr<SDL_Window> window;
    static std::shared_ptr<SDL_Surface> windowSurface;
    static std::shared_ptr<SDL_Renderer> windowRenderer;
    static std::unique_ptr<Camera> camera;

protected:
    static int width;
    static int height;
};

class Camera {
    friend class Window;

public:
    Camera();
    void update();
    void event();

    float getZoomScale();
    bool inCamera(float x, float y);
    SDL_Rect src;
    SDL_Rect dest;
    vec2 worldToScreen(float world_x, float world_y);
    vec2 screenToWorld(float screen_x, float screen_y);

    int mapHeight = 10000;
    int mapWidth = 10000;

private:
    int speed = 10;
    float zoomScale = 1;
    vec2 position = { 0, 0 };
    vec2 velocity = { 0, 0 };
};
