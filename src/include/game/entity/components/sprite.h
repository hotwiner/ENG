#pragma once

#include "../entity_component.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_stdinc.h>
#include <SDL2/SDL_surface.h>

class Sprite : public Component {
public:
    Sprite(std::string assetPath, int srcW=0, int srcH=0, int desW=0, int desH=0, int scale=1);
    virtual ~Sprite();
    void init() override;
    void update() override;
    void draw();
    std::shared_ptr<SDL_Texture> getTexture();
    std::shared_ptr<SDL_Surface> getSurface();
    void scale(int scale=1);

protected:
    // asset for the sprite
    std::string assetPath;
    SDL_Rect src; 
    SDL_Rect des;
};
