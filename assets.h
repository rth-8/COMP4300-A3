#ifndef ASSETS_H
#define ASSETS_H

#include <memory>
#include <map>

#include <SFML/Graphics.hpp>
#include <SFML/Audio/SoundBuffer.hpp>
#include <SFML/Audio/Sound.hpp>
#include "animation.h"

class Assets
{
    std::map<std::string, sf::Texture> textures;
    std::map<std::string, Animation> animations;
    std::map<std::string, sf::Font> fonts;
    std::map<std::string, sf::SoundBuffer> soundBuffers;
    std::map<std::string, sf::Sound> sounds;
    
public:
    Assets();
    
    void addTexture(const std::string& name, const std::string& path);
    void addAnimation(const std::string& name, const std::string& texname, int fc, int spd);
    void addFont(const std::string& name, const std::string& path);
    void addSound(const std::string& name, const std::string& path);
    
    sf::Texture & getTexture(const std::string& name);
    Animation & getAnimation(const std::string& name);
    sf::Font & getFont(const std::string& name);
    sf::Sound & getSound(const std::string& name);
};

#endif
