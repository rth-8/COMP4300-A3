#ifndef SCENE_PLAY_H
#define SCENE_PLAY_H

#include <SFML/Graphics/Text.hpp>

#include "scene.h"

class Entity;

class ScenePlay : public Scene
{
    struct PlayerConfig
    {
        float gx, gy, cx, cy, speed, maxspeed, jump, gravity;
        std::string weapon;
    };
    
    std::string levelPath;
    std::shared_ptr<Entity> player;
    PlayerConfig playerCfg;
    
    std::shared_ptr<sf::Text> frameText;
    
    void init();
    void load_level();
    
    bool isDrawingBB = false;
    bool isDrawingTex = true;
    
    std::string waiting;
    
    bool playerJumping = false;
    
    bool isPaused = false;
    
public:
    ScenePlay() = delete;
    ScenePlay(GameEngine* eng, const std::string & lvlP);
    ~ScenePlay();
    
    void update();
    
    void sAnimation();
    void sMovement();
    void sEnemySpawner();
    void sCollision();
    void sRender();
    void sDoAction(const Action& action);
    void sDebug();
};

#endif
