#include <iostream>
#include "animation.h"

Animation::Animation()
{
    sprite = nullptr;
}

Animation::Animation(const std::string & n, sf::Texture & tex, int fcnt, int spd)
    : name(n)
    , frameCount(fcnt)
    , speed(spd)
{
    // std::cout << "ANIMATION: c'tor: " << name << ", " << frameCount << ", " << speed << "\n";
    
    sprite = std::make_shared<sf::Sprite>(tex);
    
    currentFrame = 0;
    
    size.x = tex.getSize().x / frameCount;
    size.y = tex.getSize().y;
    
    sprite->setTextureRect(sf::IntRect({currentFrame * static_cast<int>(size.x), 0}, {static_cast<int>(size.x), static_cast<int>(size.y)}));
    sprite->setOrigin({static_cast<float>(size.x/2), static_cast<float>(size.y/2)});
}

void Animation::update(int globalFrame)
{
    if (globalFrame > 0 && speed > 0)
    {
        currentFrame = (globalFrame / speed) % frameCount;
        sprite->setTextureRect(sf::IntRect({currentFrame * static_cast<int>(size.x), 0}, {static_cast<int>(size.x), static_cast<int>(size.y)}));  
    }
}

bool Animation::hasEnded()
{
    return (currentFrame == frameCount - 1); // animation reached last frame
}

void Animation::reset()
{
    currentFrame = 0;
}

std::string & Animation::getName()
{
    return name;
}
    
Vec2 & Animation::getSize()
{
    return size;
}

sf::Sprite & Animation::getSprite()
{
    return *sprite;
}
