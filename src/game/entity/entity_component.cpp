#include "../../include/game/entity/entity_component.h"
#include "../../include/game/entity_manager.h"
#include <SDL2/SDL_stdinc.h>
#include <cmath>
#include <memory>
#include <typeinfo>

Entity::Entity(std::string n, std::string t)
    : name(n)
    , tag(t)
{
    position = { .x = 0, .y = 0 };
}

void Entity::setName(std::string n)
{
    this->name = n;
}

void Entity::setPos(vec2 pos)
{
    this->position = pos;
}

void Entity::setPos(float x, float y)
{
    this->position = { .x = x, .y = y };
}

void Entity::setTag(std::string t)
{
    this->tag = t;
}

std::string Entity::getName()
{
    return this->name;
}

std::string Entity::getTag()
{
    return this->tag;
}

void Entity::init()
{
    float a = 0;
}

void Entity::update()
{
    for (const auto& comp : this->components)
    {
        comp.second->update();
    }
}

vec2 Entity::getPosition()
{
    return this->position;
}
