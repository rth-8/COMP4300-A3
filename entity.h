#ifndef ENTITY_H
#define ENTITY_H

#include <tuple>
#include "component.h"

class EntityManager;

typedef std::tuple<
    CAnimation,
    CTransform,
    CBoundingBox,
    CLifeSpan,
    CInput,
    CGravity,
    CState
> ComponentTuple;

class Entity
{
    friend EntityManager;
    
    int id = 0;
    std::string tag = "Default";
    bool alive = true;

    ComponentTuple components;
    
    Entity() = delete;
    // c'tor is private, so only EntityManager can make Entity
    Entity(const std::string & tag, int id);
    
public:
    Entity(const Entity & src);
    ~Entity();
    
    const std::string & getTag() const;
    void kill();
    const bool isAlive() const;
    
    template <typename T> 
    T & getComponent()
    {
        return std::get<T>(components);
    }
    
    template <typename T> 
    bool hasComponent() const
    {
        return getComponent<T>().has;
    }
    
    template <typename T, typename... TArgs> 
    T & addComponent(TArgs&&... args)
    {
        auto & comp = getComponent<T>();
        comp = T(std::forward<TArgs>(args)...);
        comp.has = true;
        return comp;
    }
    
    template <typename T> 
    void removeComponent()
    {
        getComponent<T>() = T();
    }
};

#endif
