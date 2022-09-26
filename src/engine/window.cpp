#include "../include/engine/window.h"
#include "../include/engine/engine.h"
#include "../include/util/sdl_util.h"
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

int x = 0; 
int y = 0;

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
    // sdl_utils::render_whole(Window::windowSurface, Window::windowRenderer);
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
    this->src = { static_cast<int>(position.x), static_cast<int>(position.y), 1920, 1080 };
    this->dest = { static_cast<int>(position.x), static_cast<int>(position.y), 1920, 1080 };
}

void Camera::event()
{
    if (StateLoop::event->type == SDL_KEYDOWN && StateLoop::event->key.repeat == 0) {
        // Adjust the velocity
        // std::cout << "key pressed" << std::endl;
        switch (StateLoop::event->key.keysym.sym) {
        case SDLK_UP:
            this->velocity.y -= speed;
            break;
        case SDLK_DOWN:
            this->velocity.y += speed;
            break;
        case SDLK_LEFT:
            this->velocity.x -= speed;
            break;
        case SDLK_RIGHT:
            this->velocity.x += speed;
            break;
        }
    }
    // If a key was released
    else if (StateLoop::event->type == SDL_KEYUP && StateLoop::event->key.repeat == 0) {
        // Adjust the velocity
        switch (StateLoop::event->key.keysym.sym) {
        case SDLK_UP:
            this->velocity.y += speed;
            break;
        case SDLK_DOWN:
            this->velocity.y -= speed;
            break;
        case SDLK_LEFT:
            this->velocity.x += speed;
            break;
        case SDLK_RIGHT:
            this->velocity.x -= speed;
            break;
        }
    }

    if (StateLoop::event->type == SDL_MOUSEWHEEL && StateLoop::event->key.repeat == 0) {

        if (StateLoop::event->wheel.y > 0) // scroll up zoom in
        {
            zoomScale += 0.1f;
            StateLoop::event->wheel.y = 0;
        } else if (StateLoop::event->wheel.y < 0) // scroll down zoom out
        {
            zoomScale -= 0.1f;
            StateLoop::event->wheel.y = 0;
        }

        if (zoomScale <= 0.1) {
            zoomScale = 0.1;
        } else if (zoomScale >= 10) {
            zoomScale = 10;
        }

        SDL_GetMouseState(&x, &y);
        std::cout << "zooming\n";
    }
}

bool Camera::inCamera(float x, float y)
{
    bool inX = x >= this->dest.x && x <= (this->dest.x + Window::camera->dest.w);
    bool inY = y >= this->dest.y && y <= (this->dest.y + Window::camera->dest.h);
    // return true;
    return inX && inY;
}

float Camera::getZoomScale()
{
    return this->zoomScale;
}

void Camera::update()
{
    this->position += this->velocity;

    // camera position
    this->dest.x = this->position.x- x * (1 / this->zoomScale);
    this->dest.y = this->position.y- y * (1 / this->zoomScale);

    // renderable size
    this->dest.w = (1 / this->zoomScale) * this->src.w;
    this->dest.h = (1 / this->zoomScale) * this->src.h;

    std::cout << "==============================\n";
    std::cout << " Camera X: " << this->dest.x << "\n";
    std::cout << " Camera Y: " << this->dest.y << "\n";
    std::cout << " Camera Velocity: " << this->velocity.x << ", " << this->velocity.y << "\n";
    std::cout << " Renderable size W: " << this->dest.w << "\n";
    std::cout << " Renderable size H: " << this->dest.h << "\n";
    std::cout << " Zoom Scale: " << this->zoomScale << "\n";
}