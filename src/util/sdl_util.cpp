#include "../include/util/sdl_util.h"
#include "../include/engine/window.h"
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_surface.h>
#include <cmath>
#include <cstddef>
#include <memory>
#include <sys/wait.h>

std::shared_ptr<SDL_Window> sdl_utils::make_shared_window(SDL_Window* window)
{
    return std::move(std::shared_ptr<SDL_Window>(window, SDL_DestroyWindow));
}

std::shared_ptr<SDL_Renderer> sdl_utils::make_shared_renderer(SDL_Renderer* renderer)
{
    return std::move(std::shared_ptr<SDL_Renderer>(renderer, SDL_DestroyRenderer));
}

std::shared_ptr<SDL_Texture> sdl_utils::make_shared_texture(SDL_Texture* texture)
{
    return std::move(std::shared_ptr<SDL_Texture>(texture, SDL_DestroyTexture));
}

std::shared_ptr<SDL_Surface> sdl_utils::make_shared_surface(SDL_Surface* surface)
{
    // std::unique_ptr<SDL_PixelFormat> pixel_format = std::make_unique<SDL_PixelFormat>(*SDL_AllocFormat(SDL_PIXELFORMAT_RGBA32));
    // return std::move(std::shared_ptr<SDL_Surface>(SDL_ConvertSurface(surface, pixel_format.get(),0), SDL_FreeSurface));
    return std::move(std::shared_ptr<SDL_Surface>(surface, SDL_FreeSurface));
}

void sdl_utils::draw(SDL_Texture* texture, SDL_Rect* srcR, SDL_Rect* destR)
{
    SDL_RenderCopy(Window::windowRenderer.get(), texture, srcR, destR);
}

void sdl_utils::draw(std::string relativePath, SDL_Rect* srcR, SDL_Rect* destR)
{
    SDL_RenderCopy(Window::windowRenderer.get(), load_texture(relativePath).get(), srcR, destR);
}

// draws whole surface
void sdl_utils::draw_surface(SDL_Surface* surface, SDL_Rect* srcR, SDL_Rect* destR)
{
    SDL_BlitSurface(surface, srcR, Window::windowSurface.get(), destR);
}

std::shared_ptr<SDL_Texture> sdl_utils::load_texture(std::string relativePath)
{
    std::unique_ptr<SDL_Surface> img = std::make_unique<SDL_Surface>(*IMG_Load((ROOT + relativePath).c_str()));
    return make_shared_texture(SDL_CreateTextureFromSurface(Window::windowRenderer.get(), img.get()));
}

std::shared_ptr<SDL_Texture> sdl_utils::surface_to_texture(SDL_Surface* surface)
{
    return make_shared_texture(SDL_CreateTextureFromSurface(Window::windowRenderer.get(), surface));
}

std::shared_ptr<SDL_Surface> sdl_utils::load_surface(std::string relativePath)
{
    return make_shared_surface(IMG_Load((ROOT + relativePath).c_str()));
}

// Render whole surface
void sdl_utils::render_whole(std::shared_ptr<SDL_Surface> surface, std::shared_ptr<SDL_Renderer> renderer)
{
    auto windowTexture = sdl_utils::surface_to_texture(surface.get());
    SDL_RenderCopyEx(renderer.get(), windowTexture.get(), &Window::camera->src, &Window::camera->dest, 0.0, NULL, SDL_FLIP_NONE);
    SDL_FillRect(surface.get(), NULL, SDL_MapRGB(surface->format, 0, 0, 0));
}

// Render each part independently
void sdl_utils::render_independent(SDL_Texture* texture, SDL_Rect* srcR, SDL_Rect* destR)
{
    if (Window::camera->inCamera(destR->x, destR->y)) {

        SDL_Rect temp = {
            static_cast<int>(destR->x - Window::camera->dest.x),
            static_cast<int>(destR->y - Window::camera->dest.y),
            static_cast<int>(destR->w),
            static_cast<int>(destR->h)
        };
        SDL_RenderCopyEx(Window::windowRenderer.get(), texture, NULL, &temp, 0.0, NULL, SDL_FLIP_NONE);
    }
}

void sdl_utils::debug_msg()
{
    std::cout << SDL_GetError() << std::endl;
    exit(1);
}