#ifndef GAME_ENGINE_H
#define GAME_ENGINE_H

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include <map>
#include <memory>

class Assets;
class Scene;

class GameEngine
{
private:
    std::shared_ptr<sf::RenderWindow> window;
    std::shared_ptr<Assets> assets;
    std::map<std::string, std::shared_ptr<Scene> > scenes;
    std::string currentSceneId;
    bool running;
    
    void init();
    std::shared_ptr<Scene> currentScene();
    
public:
    GameEngine() = delete;
    GameEngine(std::shared_ptr<sf::RenderWindow> win);
    
    std::shared_ptr<sf::RenderWindow> getWindow();
    std::shared_ptr<Assets> getAssets();
    
    void run();
    void update();
    void quit();
    
    void addScene(const std::string& sceneId, std::shared_ptr<Scene> scene);
    void changeScene(const std::string& sceneId);
    
    void sUserInput();
};

#endif
