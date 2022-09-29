#include "../../../include/game/entity/components/transform.h"
#include "../../../include/game/entity_manager.h"
#include "../../../include/util/vec2.h"
#include <SDL2/SDL_stdinc.h>

Transform::Transform(float targetX, float targetY, float s, bool c)
    : speed(s)
    , enableCollider(c)
{
    this->target = { .x = targetX, .y = targetY };
}

Transform::~Transform()
{
}

void Transform::update()
{
    if (this->enableCollider) {
        // Check if next posiition is moveable
        vec2 currGridPos = EntityManager::collmap->toGridPos(this->entity->getPosition());
        vec2 targetGridPos = EntityManager::collmap->toGridPos(this->entity->getPosition() + this->velocity);

        if (EntityManager::collmap->updateOccupancy(currGridPos, targetGridPos)) {
            Transform::move();
        }else{
            std::cout << "cant move collide" <<  currGridPos.x << " " << currGridPos.y << std::endl;
            std::cout << "cant move collide" <<  targetGridPos.x << " " << targetGridPos.y << std::endl;
        }
    } else {
        Transform::move();
    }
}

void Transform::init()
{
    this->heading = ((this->entity->getPosition() - this->target) * -1).normalize();
    this->velocity = this->heading * this->speed;
    if (this->enableCollider) {
        vec2 pos = EntityManager::collmap->toGridPos(this->entity->getPosition());
        EntityManager::collmap->occupyPos(pos);
    }
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