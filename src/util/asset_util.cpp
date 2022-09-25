#include <SDL2/SDL.h>
#include <memory>
#include "../include/util/asset_util.h"
#include "../include/util/sdl_util.h"

std::pair<const std::string, std::pair<std::shared_ptr<SDL_Texture>, std::shared_ptr<SDL_Surface>>> asset_util::makeAsset(std::string assetPath)
{
    std::shared_ptr<SDL_Texture> texture = sdl_utils::load_texture(assetPath);
    std::shared_ptr<SDL_Surface> surface = sdl_utils::load_surface(assetPath);

    return { assetPath, {texture, surface} };
}
