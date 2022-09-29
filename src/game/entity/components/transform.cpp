#include "../../../include/game/entity/components/transform.h"
#include "../../../include/util/vec2.h"
#include <SDL2/SDL_stdinc.h>

Transform::Transform(float targetX, float targetY, float s)
    : speed(s)
{
    this->target = { .x = targetX, .y = targetY };
}

Transform::~Transform()
{
}

void Transform::update()
{
    Transform::move();
}

void Transform::init()
{
    this->heading = ((this->entity->getPosition() - this->target) * -1).normalize();
    this->velocity = this->heading * this->speed;
}

void Transform::setTarget(vec2 t)
{
    this->target = t;
    this->heading = ((this->entity->getPosition() - this->target) * -1).normalize();
    this->velocity = this->heading * this->speed;
}

vec2 Transform::move()
{
    if ((this->entity->getPosition()) != this->target) {
        if (this->entity->getPosition() + this->velocity > this->target) {
            this->entity->setPos(this->target);
        } else {
            this->entity->setPos(this->entity->getPosition() + this->velocity);
        }
    } else {
        this->entity->setPos(this->target);
    }
    return this->entity->getPosition(); 
}