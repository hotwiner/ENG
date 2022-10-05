#pragma once

#include "../../../../include/util/vec2.h"
#include "../entity_component.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_stdinc.h>
#include <vector>
#include <queue>


class Transform : public Component {
public:
    Transform(float s = 0, bool enableCollider = false);
    virtual ~Transform();
    void init() override;
    void update() override;
    void setCurrTarget(vec2 newTarget);
    void addPathTarget(vec2 newPathTarget);

protected:
    vec2 heading;
    float speed;
    bool enableCollider;

private:
    std::queue<vec2> path;
    vec2 target;
    vec2 velocity;
    vec2 move();
    vec2 updateCurrTarget();
};
