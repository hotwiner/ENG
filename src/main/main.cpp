#include "../include/engine/engine.h"
#include <bitset>
#include <cstdlib>
#include <iostream>
#include <memory>

const int entityPopulation = 1;

int main()
{
    std::unique_ptr<Engine> engine = std::make_unique<Engine>(3000, 2000);

    // sets seed for random number generator
    srand((unsigned)time(NULL));

    // populates entityMan
    for (int i = 0; i < entityPopulation; i++) {
        std::shared_ptr<Entity> entity_buffer = std::make_shared<Entity>();
        entity_buffer->addComponent<Sprite>("/assests/man2.gif", 65, 64);
        // starting position
        entity_buffer->setPos(0, 0);
        // initial movement vector
        entity_buffer->addComponent<Transform>(10,false);
        vec2 t ={600,0};
        entity_buffer->addComponent<PathFinding>(t);
        //entity_buffer->getComponent<Transform>()->addPathTarget({600,0});
        //entity_buffer->getComponent<Transform>()->addPathTarget({600,600});
        // initial sprite scale
        entity_buffer->getComponent<Sprite>()->scale(1);
        engine->stateLoop->entityMan->addEntity(entity_buffer);
    }
   
    std::cout << "Done generating " << entityPopulation << " entities.\n";

    engine->launch();

    return 0;
}
