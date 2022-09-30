#pragma once
#include "../../include/util/asset_util.h"
#include <SDL2/SDL.h>
#include <iostream>
#include <map>
#include <memory>

class AssetManager {
public:
    AssetManager();
    void loadAssets();
    static std::map<const std::string, std::pair<std::shared_ptr<SDL_Texture>, std::shared_ptr<SDL_Surface>>> assetmap;

private:
};
