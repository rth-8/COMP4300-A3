#include <iostream>

#include "assets.h"

Assets::Assets()
{
}

/*-----------------------------------------------------------------------------------------------*/

void Assets::addTexture(const std::string& name, const std::string& path)
{
    // std::cout << "ASSETS: add texture: " << name << " ( " << path << " )\n";
    this->textures.emplace(std::make_pair(name, sf::Texture(path)));
}

void Assets::addAnimation(const std::string& name, const std::string& texname, int fc, int spd)
{
    // std::cout << "ASSETS: add animation: " << name << "\n";
    auto& tex = this->getTexture(texname);
    this->animations.emplace(std::make_pair(name, Animation(name, tex, fc, spd)));
}

void Assets::addFont(const std::string& name, const std::string& path)
{
    // std::cout << "ASSETS: add font: " << name << " ( " << path << " )\n";
    this->fonts.emplace(std::make_pair(name, sf::Font(path)));
}

void Assets::addSound(const std::string& name, const std::string& path)
{
    // std::cout << "ASSETS: add sound: " << name << " ( " << path << " )\n";
    this->soundBuffers.emplace(std::make_pair(name, sf::SoundBuffer(path)));
    this->sounds.emplace(std::make_pair(name, sf::Sound(this->soundBuffers.at(name))));
    this->sounds.at(name).setVolume(50.0f);
}

/*-----------------------------------------------------------------------------------------------*/

// std::shared_ptr<sf::Texture> Assets::getTexture(const std::string& name)
sf::Texture & Assets::getTexture(const std::string& name)
{
    return this->textures.at(name);
}

Animation & Assets::getAnimation(const std::string& name)
{
    return this->animations.at(name);
}

sf::Font & Assets::getFont(const std::string& name)
{
    return this->fonts.at(name);
}

sf::Sound & Assets::getSound(const std::string& name)
{
    return this->sounds.at(name);
}
