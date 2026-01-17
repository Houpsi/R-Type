/*
** EPITECH PROJECT, 2025
** R_Type
** File description:
** ResourceManager
*/

#ifndef R_TYPE_RESOURCEMANAGER_HPP
    #define R_TYPE_RESOURCEMANAGER_HPP

#include "SFML/Audio/SoundBuffer.hpp"
#include "SFML/Graphics/Texture.hpp"
#include "SFML/Graphics/Font.hpp"
#include <string>
#include <unordered_map>

namespace ecs {
    class ResourceManager
    {
      public:
        ResourceManager();

        sf::Texture &getTexture(const std::string &);
        const sf::Font& getFont(const std::string& path);
      private:
        std::unordered_map<std::string, sf::Texture> _textureMap;
        std::unordered_map<std::string, sf::Font> _fonts;
    };
}


#endif// R_TYPE_RESOURCEMANAGER_HPP
