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
    ResourceManager::ResourceManager()
    {
        try {
            _textureMap.try_emplace("textureError.png", "assets/textureError.png");
        } catch (const std::exception &e) {
            std::cerr << "Texture loading failed: " << e.what() << '\n';
            throw std::exception();
        }
    }

    sf::Texture &ResourceManager::getTexture(const std::string &path)
    {
        if (_textureMap.contains(path)) {
            return _textureMap[path];
        }

        try {
            auto iterator = _textureMap.try_emplace(path, path).first;

            return iterator->second;
        } catch (const std::exception &e) {
            std::cerr << "Texture loading failed: " << e.what() << '\n';
            if (_textureMap.contains("textureError.png")) {
                return _textureMap["textureError.png"];
            } else {
                throw std::exception();
            }
        }
    }

    const sf::Font& ResourceManager::getFont(const std::string& path)
    {
        if (!_fonts.contains(path)) {
            sf::Font font;
            if (!font.openFromFile(path)) {
                throw std::runtime_error("Failed to load font: " + path);
            }
            _fonts.emplace(path, std::move(font));
        }
        return _fonts.at(path);
    }
}