/*
** EPITECH PROJECT, 2025
** R_Type
** File description:
** ResourceManager
*/

#include "ResourceManager.hpp"
#include <exception>
#include <iostream>
#include <string>
#include "SFML/Graphics/Texture.hpp"

namespace ecs {
    sf::Texture &ResourceManager::getTexture(std::string &path)
    {
        if (_textureMap.contains(path)) {
            return _textureMap[path];
        }

        try {
            auto iterator = _textureMap.try_emplace(path, path).first;

            return iterator->second;
        } catch (const std::exception &e) {
            std::cerr << "Texture loading failed: " << e.what() << '\n';
            // TODO throw or return "error" texture
            throw;
        }
    }
}