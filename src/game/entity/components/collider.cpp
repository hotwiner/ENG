#include "../../../include/game/entity/components/collider.h"

Collider::Collider()
{
    EntityManager::collmap->occupyPos(this->entity->getPosition().x, this->entity->getPosition().y);
}

void Collider::update()
{
    /*
    bool success = EntityManager::collmap->updateOccupancy(
        this->entity->getPosition().x, 
        this->entity->getPosition().y, 
        this->entity->getComponent<Transform>(), 
        int target_y)
        */
}