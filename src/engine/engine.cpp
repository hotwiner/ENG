#include "../include/engine/engine.h"
#include "../include/util/sdl_util.h"
#include <SDL2/SDL_render.h>
#include <memory>

Engine::Engine(int width, int height)
{
    this->stateLoop = std::make_unique<StateLoop>(width, height);

    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        sdl_utils::debug_msg();
    }
}

void Engine::launch()
{
    std::cout << "Launching..." << std::endl;
    this->stateLoop->run();
}

void Engine::terminate()
{
    this->stateLoop->stop();
}

std::unique_ptr<SDL_Event> StateLoop::event;
bool StateLoop::quit;

StateLoop::StateLoop(int width, int height)
{
    this->window = std::make_unique<Window>(Window(width, height));
    this->event = std::make_unique<SDL_Event>();
    this->entityMan = std::make_unique<EntityManager>();
}

void StateLoop::init()
{
    this->entityMan->init();
    this->quit = false;
}

// This updates everything
void StateLoop::update()
{
    this->handleEvent();

    this->startTime = SDL_GetTicks64();

    this->entityMan->update();
    this->window->update();

    this->deltaTime = SDL_GetTicks64() - this->startTime;
    if (this->timeDelay > this->deltaTime) {

        SDL_Delay(this->timeDelay - this->deltaTime);
    }
    auto fps = 1000.0f / deltaTime;
}

void StateLoop::handleEvent()
{
    //SDL_PumpEvents();

    if (SDL_PollEvent(StateLoop::event.get()) != 0) {
        if (StateLoop::event->type == SDL_QUIT) {
            StateLoop::stop();
        }

        this->window->camera->event();
    }
}

void StateLoop::stop()
{
    std::cout << "Quitting" << std::endl;
    StateLoop::quit = true;
}

void StateLoop::run()
{
    // Initialize before running the main stateLoop
    this->init();

    while (!this->quit) {
        this->window->clean();
        this->update(); // update everything
        this->window->render();
    }

    SDL_Quit();
}