#pragma once

#include "../../util/sdl_util.h"
#include "../../util/vec2.h"
#include <SDL2/SDL.h>
#include <iostream>
#include <map>
#include <memory>
#include <typeindex>
#include <typeinfo>
#include <vector>

class EntityManager;
class Entity;

// components only include scripts resources such as sprites must be reached from a single source
class Component {
public:
    virtual void init() = 0;
    virtual void update() = 0;
    std::shared_ptr<Entity> entity;

protected:
    int id;
};

class Entity : public std::enable_shared_from_this<Entity> {
    friend class EntityManager;

public:
    Entity(std::string name = "no-name", std::string tag = "no-tag");
    void setName(std::string name);
    void setTag(std::string tag);

    int getID();
    vec2 getPosition();
    vec2 getGridPosition();
    std::string getName();
    std::string getTag();

    void init();
    void update();
    void setPos(vec2 pos);
    void setPos(float x, float y);

    template <typename T, typename... TArgs>
    void addComponent(TArgs&&... mArgs)
    {
        std::shared_ptr<T> comp(new T(std::forward<TArgs>(mArgs)...));
        comp->entity = shared_from_this();
        comp->init();
        this->components.insert({ typeid(T), comp });
    }

    template <typename T>
    std::shared_ptr<T> getComponent() const
    {
        return std::dynamic_pointer_cast<T>(this->components.at(typeid(T)));
    }

protected:
    std::map<std::type_index, std::shared_ptr<Component>> components;
    int id;
    vec2 position;
    std::string tag;
    std::string name;
};
