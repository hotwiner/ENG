#pragma once

#include "../../util/sdl_util.h"
#include "../../util/vec2.h"
#include <SDL2/SDL.h>
#include <iostream>
#include <map>
#include <memory>
#include <stdexcept>
#include <string>
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
    
    std::string getName();
    std::string getTag();

    void init();
    void update();
    void setPos(vec2 pos);
    void setPos(float x, float y);

    template <typename T>
    bool hasComponent()
    {
        return (this->components.find(typeid(T)) != this->components.end());
    }

    template <typename T>
    void requireComponent()
    {
        if (!hasComponent<T>()) {
            throw std::logic_error(typeid(T).name());
        }
    }

    template <typename T, typename... TArgs>
    void addComponent(TArgs&&... mArgs)
    {
        if (!hasComponent<T>()) {
            std::shared_ptr<T> comp(new T(std::forward<TArgs>(mArgs)...));
            comp->entity = shared_from_this();
            comp->init();
            this->components.insert({ typeid(T), comp });
        }
    }

    template <typename T>
    std::shared_ptr<T> getComponent()
    {
        if (hasComponent<T>()) {
            return std::dynamic_pointer_cast<T>(this->components.at(typeid(T)));
        }
        return nullptr;
    }

protected:
    std::map<std::type_index, std::shared_ptr<Component>> components;
    int id;
    vec2 position;
    std::string tag;
    std::string name;
};
