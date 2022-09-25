#pragma once

#include "../../../setup_info.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_surface.h>
#include <iostream>
#include <memory>

namespace sdl_utils {

    std::shared_ptr<SDL_Window> make_shared_window(SDL_Window* window);
    std::shared_ptr<SDL_Renderer> make_shared_renderer(SDL_Renderer* renderer);
    std::shared_ptr<SDL_Texture> make_shared_texture(SDL_Texture* texture);
    std::shared_ptr<SDL_Surface> make_shared_surface(SDL_Surface* surface);

    std::shared_ptr<SDL_Texture> load_texture(std::string relativePath);
    std::shared_ptr<SDL_Surface> load_surface(std::string relativePath);
    std::shared_ptr<SDL_Texture> surface_to_texture(SDL_Surface* surface);

    void draw(SDL_Texture* texture, SDL_Rect* srcR, SDL_Rect* destR);
    void draw(std::string relativePath, SDL_Rect* srcR, SDL_Rect* destR);

    // Draws independent surfaces on the window surface
    void draw_surface(SDL_Surface* surface, SDL_Rect* srcR, SDL_Rect* destR);

    void render_whole(std::shared_ptr<SDL_Surface> surface, std::shared_ptr<SDL_Renderer> renderer);
    void render_independent(SDL_Texture* texture, SDL_Rect* srcR, SDL_Rect* destR);

    void debug_msg();
}