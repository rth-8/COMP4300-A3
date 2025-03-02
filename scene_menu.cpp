#include <iostream>
#include "scene_menu.h"
#include "game_engine.h"
#include "assets.h"
#include "scene_play.h"

SceneMenu::SceneMenu(GameEngine* eng) 
    : Scene(eng)
    , menuIndex(0)
{
    // std::cout << "SCENE MENU: c'tor\n";
    init();
}

void SceneMenu::init()
{
    registerAction(static_cast<int>(sf::Keyboard::Scancode::Escape), "ENDAPP");
    registerAction(static_cast<int>(sf::Keyboard::Scancode::Num1), "STARTLEVEL1");
    registerAction(static_cast<int>(sf::Keyboard::Scancode::Num2), "STARTLEVEL2");
    
    menuStrings.push_back("Title\n");
    menuStrings.push_back("Level 1\n");
    menuStrings.push_back("Level 2\n");
    
    levelPaths.push_back("data/level1.txt");
    levelPaths.push_back("data/level2.txt");
    
    menuText = std::make_shared<sf::Text>(this->engine->getAssets()->getFont("MenuFont"));
    menuText->setCharacterSize(48);
    menuText->setFillColor(sf::Color::Black);
    menuText->setPosition({20,20});
}

void SceneMenu::update()
{
    sRender();
}

void SceneMenu::sRender()
{
    auto w = this->engine->getWindow();
    w->clear(sf::Color::Green);
    
    menuText->setString(menuStrings[0]);
    w->draw(*menuText);
}

void SceneMenu::sDoAction(const Action& action)
{
    // std::cout << "SCENE MENU: do action: " << action.name() << " (" << action.type() << ")\n";
    if (action.type() == "START")
    {
        if (action.name() == "ENDAPP")
        {
            this->engine->quit();
        }
        else
        if (action.name() == "STARTLEVEL1")
        {
            this->engine->addScene("Play", std::make_shared<ScenePlay>(this->engine, levelPaths[0]));
            this->engine->changeScene("Play");
        }
        else
        if (action.name() == "STARTLEVEL2")
        {
            this->engine->addScene("Play", std::make_shared<ScenePlay>(this->engine, levelPaths[1]));
            this->engine->changeScene("Play");
        }
    }
}
