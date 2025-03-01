#ifndef ANIMATION_H
#define ANIMATION_H

#include <string>
#include <memory>
#include <SFML/Graphics.hpp>
#include "vector2d.h"

class Animation
{
    std::string name;
    std::shared_ptr<sf::Sprite> sprite;
    Vec2 size;
    int frameCount;
    int currentFrame;
    int speed;
    
public:
    Animation();
    Animation(const std::string & n, sf::Texture & tex, int fcnt, int spd);
    
    void update(int globalFrame);
    bool hasEnded();
    std::string & getName();
    Vec2 & getSize();
    sf::Sprite & getSprite();
};

#endif
