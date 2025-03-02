#include <iostream>
#include <memory>

#include "entity_manager.h"
#include "entity.h"

EntityManager::EntityManager()
{
    // std::cout << "MANAGER: c'tor\n";
}

std::shared_ptr<Entity> EntityManager::addEntity(const std::string & tag)
{
    // std::shared_ptr<Entity> e = std::make_shared<Entity>(new Entity(tag, ++totalEntities));
    auto e = std::shared_ptr<Entity>(new Entity(tag, ++totalEntities)); // hacky way of creating new entity (because make_shared can't reach private constructor of Entity)
    this->toBeAdded.push_back(e);
    return e;
}

EntityVector & EntityManager::getEntities()
{
    return this->entities;
}
    
EntityVector & EntityManager::getEntities(const std::string & tag)
{
    return this->entityMap[tag];
}
    
void EntityManager::update()
{
    // std::cout << "MANAGER: update\n";
    
    // https://en.cppreference.com/w/cpp/container/vector/erase
    
    for (auto it = this->entities.begin(); it != this->entities.end();)
    {
        if ((*it)->isAlive() == false)
        {
            for (auto it2 = this->entityMap[(*it)->getTag()].begin(); it2 != this->entityMap[(*it)->getTag()].end();)
            {
                if ((*it2)->isAlive() == false)
                {
                    // std::cout << "MANAGER: Delayed removing of entity from map\n";
                    this->entityMap[(*it)->getTag()].erase(it2);
                }
                else
                    ++it2;
            }
            
            // std::cout << "MANAGER: Delayed removing of entity from vector (" << (*it)->getTag() << ")\n";
            it = this->entities.erase(it);
        }
        else
            ++it;
    }
    
    for (auto e : this->toBeAdded)
    {
        // std::cout << "MANAGER: Delayed adding of entity (" << e->getTag() << ")\n";
        this->entities.push_back(e);
        this->entityMap[e->getTag()].push_back(e);
    }
    this->toBeAdded.clear();
}
