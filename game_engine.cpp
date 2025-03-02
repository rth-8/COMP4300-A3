#include <iostream>
#include <fstream>

#include "game_engine.h"
#include "animation.h"
#include "assets.h"
#include "scene_menu.h"
#include "scene_play.h"
#include "action.h"

GameEngine::GameEngine(std::shared_ptr<sf::RenderWindow> win)
    : window(win)
{
    assets = std::make_shared<Assets>();
    init();
}

void GameEngine::init()
{
    std::fstream input;

    input.open("data/assets.dat", std::ios::in);
    if (input.is_open())
    {
        std::string line;
        while (std::getline(input, line))
        {
            // std::cout << "LINE: " << line << '\n';
            
            if (line[0] == '#')
                continue;
            
            std::stringstream ss(line);
            std::string token;
            
            std::string sval1;
            std::string sval2;
            int ival1;
            int ival2;
            
            if (std::getline(ss, token, ' '))
            {
                if (token == "Texture")
                {
                    ss >> sval1 >> sval2;
                    assets->addTexture(sval1, sval2);
                }
                else
                if (token == "Animation")
                {
                    ss >> sval1 >> sval2 >> ival1 >> ival2;
                    assets->addAnimation(sval1, sval2, ival1, ival2);
                }
                else
                if (token == "Font")
                {
                    ss >> sval1 >> sval2;
                    assets->addFont(sval1, sval2);
                }
            }
        }
        
        input.close();
    }
    
    this->addScene("Menu", std::make_shared<SceneMenu>(this));
    this->changeScene("Menu");
}

std::shared_ptr<sf::RenderWindow> GameEngine::getWindow()
{
    return window;
}

std::shared_ptr<Assets> GameEngine::getAssets()
{
    return assets;
}

void GameEngine::addScene(const std::string& sceneId, std::shared_ptr<Scene> scene)
{
    this->scenes[sceneId] = scene;
}

std::shared_ptr<Scene> GameEngine::currentScene()
{
    return scenes[currentSceneId];
}

void GameEngine::changeScene(const std::string& sceneId)
{
    // std::cout << "ENGINE: change scene: " << sceneId << "\n";
    currentSceneId = sceneId;
}

void GameEngine::run()
{
    running = true;
    
    while (running)
    {        
        if (running)
        {
            window->clear(sf::Color::Black);
            this->sUserInput();
            this->update();
            window->display();
        }
    }
}

void GameEngine::update()
{
    this->currentScene()->update();
}

void GameEngine::quit()
{
    // std::cout << "ENGINE: quit\n";
    running = false;
}

void GameEngine::sUserInput()
{
    while (const std::optional event = window->pollEvent())
    {
        if (event->is<sf::Event::Closed>())
        {
            quit();
        }
        
        const auto* keyPressed = event->getIf<sf::Event::KeyPressed>();
        const auto* keyReleased = event->getIf<sf::Event::KeyReleased>();
        
        if (keyPressed)
        {
            int scancode = static_cast<int>(keyPressed->scancode);
            if (currentScene()->actionExists(scancode))
            {
                currentScene()->sDoAction(Action(currentScene()->getActionMap().at(scancode), "START"));
            }
        }
        
        if (keyReleased)
        {
            int scancode = static_cast<int>(keyReleased->scancode);
            if (currentScene()->actionExists(scancode))
            {
                currentScene()->sDoAction(Action(currentScene()->getActionMap().at(scancode), "END"));
            }
        }
    }
}
