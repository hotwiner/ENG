#include "../include/engine/engine.h"
#include <bitset>
#include <iostream>
#include <memory>

const int entityPopulation = 1;

int main()
{
    std::unique_ptr<Engine> engine = std::make_unique<Engine>();

    // sets seed for random number generator
    srand((unsigned)time(NULL));

    // populates entityMan
    for (int i = 0; i < entityPopulation; i++) {
        std::shared_ptr<Entity> entity_buffer = std::make_shared<Entity>();
        entity_buffer->addComponent<Sprite>("/assests/man2.gif", 65, 64);
        // starting position
        entity_buffer->setPos(0, 0);
        // initial movement vector
        entity_buffer->addComponent<Transform>(600, 600, 2, true);
        // initial sprite scale
        entity_buffer->getComponent<Sprite>()->scale(1);
        engine->stateLoop->entityMan->addEntity(entity_buffer);
    }
    for (int i = 0; i < 1000; i++) {
        auto p = engine->stateLoop->entityMan->collmap->toGridPos({500, static_cast<float>(i)});
        engine->stateLoop->entityMan->collmap->occupyPos(p);
    }
    std::cout << "Done generating " << entityPopulation << " entities.\n";

    engine->launch();

    return 0;
}
