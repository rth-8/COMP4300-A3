#include <iostream>
#include <SFML/Window.hpp>
#include <memory>
#include "game_engine.h"

int main()
{
    auto window = std::make_shared<sf::RenderWindow>(sf::VideoMode({800, 600}), "COMP4300 A3", sf::Style::Close, sf::State::Windowed);
    window->setFramerateLimit(60);
    window->setKeyRepeatEnabled(false);

    auto engine = std::make_shared<GameEngine>(window);
    
    if (window->isOpen())
    {
        engine->run();
    }
    
    // std::cout << "Closing window...\n";
    window->close();
    
    return 0;
}
