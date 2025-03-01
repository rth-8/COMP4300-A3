#ifndef SCENE_MENU_H
#define SCENE_MENU_H

#include <vector>
#include <SFML/Graphics/Text.hpp>

#include "scene.h"

class Entity;

class SceneMenu : public Scene
{
    std::vector<std::string> menuStrings;
    std::shared_ptr<sf::Text> menuText;
    int menuIndex;
    
    std::vector<std::string> levelPaths;
    
    void init();
    
public:
    SceneMenu() = delete;
    SceneMenu(GameEngine* eng);
    
    void update();
    
    void sRender();
    void sDoAction(const Action& action);
};

#endif
