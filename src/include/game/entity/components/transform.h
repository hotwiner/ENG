#pragma once

#include "../../../../include/util/vec2.h"
#include "../entity_component.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_stdinc.h>

class Transform : public Component {
public:
    Transform(float targetX = 0, float targetY = 0, float s = 0);
    virtual ~Transform();
    void init() override;
    void update() override;
    void setTarget(vec2 t);

protected:
    vec2 heading;
    float speed;

private:
    void move();
    vec2 target;
    vec2 velocity;
};