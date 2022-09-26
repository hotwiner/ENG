#include "../include/engine/engine.h"
#include <cstdlib>
#include <iostream>
#include <memory>

const int entityPopulation = 1000;

int main()
{
    std::unique_ptr<Engine> engine = std::make_unique<Engine>();
    
    //sets seed for random number generator
    srand( (unsigned)time(NULL) );

    // populates entityMan
    for (int i = 0; i < entityPopulation; i++) {
        std::shared_ptr<Entity> entity_buffer = std::make_shared<Entity>(); // --------------------------- bunu niye shared yaptin?
        entity_buffer->addComponent<Sprite>("/assests/man2.gif", 65, 64);
        //starting position
        entity_buffer->setPos( rand()%1000,rand()%1000);
        //initial movement vector
        entity_buffer->addComponent<Transform>(rand()%10000,rand()%10000, rand()%5);
        //initial sprite scale
        entity_buffer->getComponent<Sprite>()->scale(1);
        engine->stateLoop->entityMan->addEntity(entity_buffer);
    }
    
    std::cout << "Done generating " << entityPopulation << " entities.\n";

    engine->launch();
    return 0;
}
