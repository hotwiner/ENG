#include "../../../include/game/entity/components/transform.h"
#include "../../../include/game/map_manager.h"
#include "../../../include/util/vec2.h"
#include <SDL2/SDL_stdinc.h>

Transform::Transform(float s, bool c)
    : speed(s)
    , enableCollider(c)
{
}

Transform::~Transform()
{
}

void Transform::init()
{
    this->target = this->entity->getPosition();
    Transform::updateCurrTarget();
}

void Transform::update()
{
    Transform::move();
}

void Transform::setCurrTarget(vec2 newTarget)
{
    this->target = newTarget;
    this->heading = ((this->entity->getPosition() - this->target) * -1).normalize();
    this->velocity = this->heading * this->speed;
}

void Transform::addPathTarget(vec2 newPathTarget)
{
    this->path.push(newPathTarget);
}

vec2 Transform::move()
{
    if (speed > 0) {
        auto leftDist = this->entity->getPosition() - this->target;
        if ((this->entity->getPosition()) == this->target || this->velocity.magnitude() > leftDist.magnitude()) {
            this->entity->setPos(this->target);
            Transform::updateCurrTarget();
        } else {
            this->entity->setPos(this->entity->getPosition() + this->velocity);
        }
    }
    return this->entity->getPosition();
}

vec2 Transform::updateCurrTarget()
{
    if (!path.empty()) {
        this->setCurrTarget(path.front());
        this->path.pop();
    }
    return this->target;
}