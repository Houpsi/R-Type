/*
** EPITECH PROJECT, 2025
** R_Type
** File description:
** Sprite
*/

#include "Sprite.hpp"

namespace ECS {
Sprite::Sprite(const std::string& texturePath)
    : _texture()
      , _sprite(_texture)
{
    if (!_texture.loadFromFile(texturePath)) {
        throw std::runtime_error("Failed to load texture: " + texturePath);
    }
    _sprite.setTexture(_texture, true);
}

const sf::Sprite& Sprite::getSprite() const
{
    return _sprite;
}
}
