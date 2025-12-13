/*
** EPITECH PROJECT, 2025
** R_Type
** File description:
** ResourceManager
*/

#ifndef R_TYPE_RESOURCEMANAGER_HPP
    #define R_TYPE_RESOURCEMANAGER_HPP

#include "SFML/Graphics/Texture.hpp"
#include <string>
#include <unordered_map>

namespace ecs {
    class ResourceManager
    {
      public:
        ResourceManager() = default;

        sf::Texture &getTexture(std::string &);
      private:
        std::unordered_map<std::string, sf::Texture> _textureMap;
    };
}


#endif// R_TYPE_RESOURCEMANAGER_HPP
