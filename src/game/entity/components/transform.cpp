#include "../../../include/game/entity/components/transform.h"
#include "../../../include/util/vec2.h"
#include <SDL2/SDL_stdinc.h>

Transform::Transform(float targetX, float targetY, float s): speed(s)
{
    this->target = {.x = targetX, .y = targetY};
}

Transform::~Transform()
{}

void Transform::update()
{
    Transform::move();
}

void Transform::init()
{
    this->heading = ((this->entity->getPosition() - this->target)*-1).normalize();
    this->velocity = this->heading * this->speed;
}

void Transform::setTarget(vec2 t)
{
    this->target = t;
}

void Transform::move()
{
    if (this->entity->getPosition() != this->target || true) {
        this->entity->setPos(this->entity->getPosition() + this->velocity);
    }
}