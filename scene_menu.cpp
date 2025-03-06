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
    this->view = this->view = engine->getWindow()->getDefaultView();
    init();
}

void SceneMenu::init()
{
    registerAction(static_cast<int>(sf::Keyboard::Scancode::Escape), "ENDAPP");
    
    registerAction(static_cast<int>(sf::Keyboard::Scancode::Up), "MENUUP");
    registerAction(static_cast<int>(sf::Keyboard::Scancode::Down), "MENUDOWN");
    registerAction(static_cast<int>(sf::Keyboard::Scancode::Enter), "MENUSELECT");
    
    registerAction(static_cast<int>(sf::Keyboard::Scancode::Num1), "STARTLEVEL1");
    registerAction(static_cast<int>(sf::Keyboard::Scancode::Num2), "STARTLEVEL2");
    
    menuStrings.push_back("My Platformer Game\n");
    menuStrings.push_back("1. Level 1\n");
    menuStrings.push_back("2. Level 2\n");
    
    levelPaths.push_back("data/level1.txt");
    levelPaths.push_back("data/level2.txt");
    
    auto& font = this->engine->getAssets()->getFont("MenuFont");
    std::vector<float> sizes{80, 48, 48};
    float y = 40.0f;
    
    menuTexts.resize(menuStrings.size());
    for (std::size_t i{}; i < menuStrings.size(); ++i)
    {
        menuTexts[i] = std::make_shared<sf::Text>(font);
        menuTexts[i]->setString(menuStrings[i]); 
        menuTexts[i]->setCharacterSize(sizes[i]);
        menuTexts[i]->setFillColor(sf::Color::Black);
        menuTexts[i]->setPosition(sf::Vector2f(20.0f, y));
        y += menuTexts[i]->getGlobalBounds().size.y;
    }
    menuTexts[menuIndex+1]->setFillColor(sf::Color::Yellow);
}

void SceneMenu::update()
{
    sRender();
}

void SceneMenu::sRender()
{
    auto w = this->engine->getWindow();
    w->clear(sf::Color(92,148,252));
    
    w->setView(this->view);
    
    for (std::shared_ptr<sf::Text> t : menuTexts)
    {
        w->draw(*t);
    }
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
        if (action.name() == "MENUUP")
        {
            if (menuIndex > 0)
                menuIndex--;
            
            menuTexts[menuIndex+1]->setFillColor(sf::Color::Yellow);
            menuTexts[menuIndex+2]->setFillColor(sf::Color::Black);
        }
        else
        if (action.name() == "MENUDOWN")
        {
            if (menuIndex < levelPaths.size()-1)
                menuIndex++;
            
            menuTexts[menuIndex+1]->setFillColor(sf::Color::Yellow);
            menuTexts[menuIndex]->setFillColor(sf::Color::Black);
        }
        else
        if (action.name() == "MENUSELECT")
        {
            this->engine->addScene("Play", std::make_shared<ScenePlay>(this->engine, levelPaths[menuIndex]));
            this->engine->changeScene("Play");
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
