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
        entity_buffer->addComponent<Transform>(500, 500, 1);
        // initial sprite scale
        entity_buffer->getComponent<Sprite>()->scale(1);
        engine->stateLoop->entityMan->addEntity(entity_buffer);
    }

    std::cout << "Done generating " << entityPopulation << " entities.\n";

    engine->launch();

    return 0;
}
