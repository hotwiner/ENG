#pragma once

#include "../../include/game/asset_manager.h"
#include "../../include/game/entity_manager.h"
#include "../../include/game/map_manager.h"
#include "window.h"
#include <SDL2/SDL.h>
#include <iostream>
#include <memory>

class StateLoop {
    friend class Engine;

public:
    StateLoop(int width, int height);
    void run();
    static void stop();

    void init();
    void update();
    void handleEvent();

    // Main window controller
    std::unique_ptr<Window> window;
    // Handles key inputs ect.
    static std::unique_ptr<SDL_Event> event;
    static const Uint8* keyboardState;
    // Handles entities
    std::unique_ptr<EntityManager> entityMan;
    // Handles mapping
    std::unique_ptr<MapManager> mapMan;
    // Handles assets
    std::unique_ptr<AssetManager> assetMan;

protected:
    static bool quit;
    const Uint32 FPS = 60;
    const Uint32 timeDelay = 1000 / FPS;

    Uint32 startTime = 0;
    Uint32 deltaTime = 0;
};

class Engine {
public:
    Engine(int width = 1920, int height = 1080);
    void launch();
    void terminate();
    std::unique_ptr<StateLoop> stateLoop;
};