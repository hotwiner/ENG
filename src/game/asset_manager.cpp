#include "../include/game/asset_manager.h"

std::map<const std::string, std::pair<std::shared_ptr<SDL_Texture>, std::shared_ptr<SDL_Surface>>> AssetManager::assetmap;

AssetManager::AssetManager()
{

}

void AssetManager::loadAssets()
{
    // Initialize all usable asset textures
    AssetManager::assetmap = {
        asset_util::makeAsset("/assests/dog.png"),
        asset_util::makeAsset("/assests/man.gif"),
        asset_util::makeAsset("/assests/man2.gif"),
        asset_util::makeAsset("/assests/grid.png"),
        asset_util::makeAsset("/assests/wall.png")
    };
}