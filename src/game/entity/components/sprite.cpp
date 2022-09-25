#include "../../../include/game/entity/components/sprite.h"
#include "../../../include/game/entity_manager.h"
#include "../../../include/util/sdl_util.h"
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_surface.h>

// x, y for destination on the window surface
Sprite::Sprite(std::string ap, int srcW, int srcH, int desW, int desH, int scale)
    : assetPath(ap)
{
    this->src = { .x = 0, .y = 0, .w = srcW, .h = srcH };

    if (desW == 0 && 0 == desH) {
        this->des = { .x = 0, .y = 0, .w = srcW * scale, .h = srcH * scale };
    } else {
        this->des = { .x = 0, .y = 0, .w = desW * scale, .h = desH * scale };
    }
}

Sprite::~Sprite()
{
}

void Sprite::draw()
{
    sdl_utils::render_independent(this->getTexture().get(), &this->src, &this->des);
}

void Sprite::update()
{
    this->des.x = this->entity->getPosition().x;
    this->des.y = this->entity->getPosition().y;
    draw();
}

void Sprite::init()
{
    this->des.x = static_cast<float>(this->entity->getPosition().x);
    this->des.y = static_cast<float>(this->entity->getPosition().y);
}

std::shared_ptr<SDL_Texture> Sprite::getTexture()
{
    return EntityManager::assetmap.at(this->assetPath).first;
}

std::shared_ptr<SDL_Surface> Sprite::getSurface()
{
    return EntityManager::assetmap.at(this->assetPath).second;
}

void Sprite::scale(int scale)
{
    this->des.h *= scale;
    this->des.w *= scale;
}