
#include <SDL2/SDL.h>
#include <iostream>
#include <memory>

namespace asset_util {
    std::pair<const std::string, std::pair<std::shared_ptr<SDL_Texture>, std::shared_ptr<SDL_Surface>>> makeAsset(std::string assetPath);
}