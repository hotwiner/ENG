#include "../include/engine/engine.h"
#include <cstdlib>
#include <iostream>
#include <memory>

int main()
{
    std::unique_ptr<Engine> engine = std::make_unique<Engine>();
    
    srand( (unsigned)time(NULL) );

    for (int i = 0; i < 1000; i++) {
        
        std::shared_ptr<Entity> entity = std::make_shared<Entity>();
        entity->addComponent<Sprite>("/assests/man2.gif", 65, 64);
        entity->setPos( rand()%1000,rand()%1000);
        entity->addComponent<Transform>(rand()%10000,rand()%10000, 0);
        entity->getComponent<Sprite>()->scale(1);
        engine->stateLoop->entityMan->addEntity(entity);
    }
    
    std::cout << "Done loading entities\n";

    engine->launch();
    return 0;
}