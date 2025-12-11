/*
** EPITECH PROJECT, 2025
** R_Type
** File description:
** Sprite
*/

#include "Sprite.hpp"

namespace ecs {
Sprite::Sprite(const std::string& texturePath) :
      _sprite(_texture)
{
    if (!_texture.loadFromFile(texturePath)) {
        throw std::runtime_error("Failed to load texture: " + texturePath);
    }
    _sprite.setTexture(_texture);
}


const sf::Sprite& Sprite::getSprite() const
{
    return _sprite;
}

void Sprite::setTextureRect(int x, int y, int width, int height)
{
    _sprite.setTextureRect(sf::IntRect(sf::Vector2i(x, y), sf::Vector2i(width, height)));
};

}
