#pragma once

#include "../entity_component.h"
#include "../../entity_manager.h"

class Collider : public Component {
public:
    Collider();
    virtual ~Collider();
    void init() override;
    void update() override;
  
protected:

};
