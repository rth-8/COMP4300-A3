#ifndef ENTITY_MANAGER_H
#define ENTITY_MANAGER_H

#include <vector>
#include <map>

class Vec2;
class Entity;

typedef std::vector<std::shared_ptr<Entity> > EntityVector;
typedef std::map<std::string, EntityVector> EntityMap;

class EntityManager
{
    EntityVector entities;
    EntityVector toBeAdded;
    EntityMap entityMap;
    int totalEntities = 0;
    
public:
    EntityManager();
    
    std::shared_ptr<Entity> addEntity(const std::string & tag);
    
    EntityVector & getEntities();
    EntityVector & getEntities(const std::string & tag);
    
    void update();
    
    void printEntities();
};

#endif
