#include "../include/engine/window.h"
#include "../../setup_info.h"
#include "../include/engine/engine.h"
#include "../include/util/sdl_util.h"
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_keycode.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_video.h>
#include <cmath>
#include <cstddef>
#include <iostream>
#include <memory>
#include <ostream>

std::shared_ptr<SDL_Window> Window::window;
std::shared_ptr<SDL_Renderer> Window::windowRenderer;
std::shared_ptr<SDL_Surface> Window::windowSurface;
std::unique_ptr<Camera> Window::camera;

int Window::height;
int Window::width;

Window::Window(int w, int h)
{
    Window::height = h;
    Window::width = w;
    Window::window = sdl_utils::make_shared_window(SDL_CreateWindow("Engine", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, this->width, this->height, SDL_WINDOW_OPENGL));
    Window::windowRenderer = sdl_utils::make_shared_renderer(SDL_CreateRenderer(window.get(), -1, SDL_RENDERER_ACCELERATED));
    Window::windowSurface = sdl_utils::make_shared_surface(SDL_CreateRGBSurface(0, 10000, 10000, 32, 0, 0, 0, 0));
    Window::camera = std::make_unique<Camera>();
}

void Window::update()
{
    this->camera->update();
}

void Window::clean()
{
    SDL_RenderClear(Window::windowRenderer.get());
}

void Window::render()
{
    SDL_RenderPresent(Window::windowRenderer.get());
}

Camera::Camera()
{
    this->src = { static_cast<int>(position.x), static_cast<int>(position.y), Window::width, Window::height };
    this->dest = { static_cast<int>(position.x), static_cast<int>(position.y), Window::width, Window::height };
}

void Camera::event()
{
    speed = 10 * (1 / zoomScale);
    if (StateLoop::event->type == SDL_KEYDOWN && StateLoop::event->key.repeat == 0) {
        // Adjust the velocity
        // std::cout << "key pressed" << std::endl;
        if (StateLoop::event->key.repeat == 0) {
            switch (StateLoop::event->key.keysym.sym) {
            case SDLK_w:
                this->velocity.y -= speed;
                break;
            case SDLK_s:
                this->velocity.y += speed;
                break;
            case SDLK_a:
                this->velocity.x -= speed;
                break;
            case SDLK_d:
                this->velocity.x += speed;
                break;
            }
        }
    }
    if (StateLoop::event->type == SDL_KEYUP && StateLoop::event->key.repeat == 0) {
        // Adjust the velocity
        switch (StateLoop::event->key.keysym.sym) {
        case SDLK_w:
            this->velocity.y = 0;
            break;
        case SDLK_s:
            this->velocity.y = 0;
            break;
        case SDLK_a:
            this->velocity.x = 0;
            break;
        case SDLK_d:
            this->velocity.x = 0;
            break;
        }
    }

    if (StateLoop::event->type == SDL_MOUSEWHEEL) {

        int cursor_x, cursor_y;

        SDL_PumpEvents();
        SDL_GetMouseState(&cursor_x, &cursor_y);

        auto befZoom = screenToWorld(cursor_x, cursor_y);

        if (StateLoop::event->wheel.y > 0) // scroll up zoom in
        {
            // std::cout << "zoom in: " << StateLoop::event->wheel.preciseY << std::endl;
            zoomScale *= 1.1f;
            StateLoop::event->wheel.y = 0;

        } else if (StateLoop::event->wheel.y < 0) // scroll down zoom out
        {
            // std::cout << "zoom out: " << StateLoop::event->wheel.preciseY << std::endl;
            zoomScale *= 0.9f;
            StateLoop::event->wheel.y = 0;
        }

        SDL_PumpEvents();
        SDL_GetMouseState(&cursor_x, &cursor_y);

        auto aftZoom = screenToWorld(cursor_x, cursor_y);
        auto diff = befZoom - aftZoom;

        this->position.x += diff.x;
        this->position.y += diff.y;
    }
}

bool Camera::inCamera(float x, float y)
{
    bool inX = x >= this->position.x && x <= (this->position.x + Window::camera->dest.w);
    bool inY = y >= this->position.y && y <= (this->position.y + Window::camera->dest.h);

    return inX && inY;
}

float Camera::getZoomScale()
{
    return this->zoomScale;
}

vec2 Camera::worldToScreen(float world_x, float world_y)
{
    return { (world_x - this->position.x) * (zoomScale), (world_y - this->position.y) * (zoomScale) };
}

vec2 Camera::screenToWorld(float screen_x, float screen_y)
{
    return { (screen_x / zoomScale) + position.x, (screen_y / zoomScale) + position.y };
}

void Camera::update()
{
    SDL_RenderSetScale(Window::windowRenderer.get(), zoomScale, zoomScale);
    this->position += this->velocity;

    // renderable size
    this->dest.w = (1 / this->zoomScale) * this->src.w;
    this->dest.h = (1 / this->zoomScale) * this->src.h;

    //  camera position
    this->dest.x = static_cast<int>(this->position.x);
    this->dest.y = static_cast<int>(this->position.y);

#if DEBUG
    int x, y;
    SDL_PumpEvents();
    SDL_GetMouseState(&x, &y);
    std::cout << "==============================\n";
    std::cout << " cursor X: " << screenToWorld(x, y).x << "\n";
    std::cout << " cursor Y: " << screenToWorld(x, y).y << "\n";
    std::cout << " Camera Velocity: " << this->velocity.x << ", " << this->velocity.y << "\n";
    std::cout << " Renderable size W: " << this->dest.w << "\n";
    std::cout << " Renderable size H: " << this->dest.h << "\n";
    std::cout << " Zoom Scale: " << this->zoomScale << "\n";
#endif
}