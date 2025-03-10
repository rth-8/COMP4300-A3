#ifndef SCENE_PLAY_H
#define SCENE_PLAY_H

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/View.hpp>
#include <SFML/Graphics/Text.hpp>

#include "scene.h"

class Entity;

class ScenePlay : public Scene
{
    sf::View view;
    
    struct PlayerConfig
    {
        float gx, gy, cx, cy, speed, maxspeed, jump, gravity;
        std::string weapon;
    };
    
    std::string levelPath;
    int levelW;
    int windowW;
    int windowH;
    int windowW2;
    int windowH2;
    
    std::shared_ptr<Entity> player;
    PlayerConfig playerCfg;
    
    void init();
    void load_level();
    
    sf::RenderTexture gridTex;
    std::shared_ptr<sf::Sprite> gridSprite;
    void create_grid();
    
    bool isDrawingBB = false;
    bool isDrawingTex = true;
    bool isDrawingGrid = false;
    
    std::string waiting;
    
    bool playerInAir = false;
    
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
