#ifndef SCENE_H
#define SCENE_H

#include <memory>
#include <map>

#include "action.h"

class GameEngine;
class EntityManager;

typedef std::map<int, std::string> ActionMap;

class Scene
{
protected:
    GameEngine* engine;
    std::shared_ptr<EntityManager> manager;
    ActionMap actionMap;
    int currentFrame;
    bool paused;
    bool hasEnded;

public:
    Scene() = delete;
    Scene(GameEngine* eng);
    
    virtual void update() = 0;
    virtual void sDoAction(const Action& action) = 0;
    virtual void sRender() = 0;
    
    void registerAction(int key, const std::string& name);
    bool actionExists(int key) const;
    const ActionMap & getActionMap() const;
};

#endif
