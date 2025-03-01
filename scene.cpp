#include "scene.h"
#include "entity_manager.h"

Scene::Scene(GameEngine* eng) 
    : engine(eng)
    , currentFrame(0)
{
    this->manager = std::make_shared<EntityManager>();
}

void Scene::registerAction(int key, const std::string& name)
{
    this->actionMap[key] = name;
}

bool Scene::actionExists(int key) const
{
    return this->actionMap.contains(key);
}

const ActionMap & Scene::getActionMap() const
{
    return this->actionMap;
}
