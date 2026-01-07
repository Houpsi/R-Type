/*
** EPITECH PROJECT, 2025
** R_Type
** File description:
** Sprite
*/

#include "Sprite.hpp"

namespace ecs {
Sprite::Sprite(sf::Texture &texture, const sf::Vector2f &scale) :
      _sprite(texture), _scale(scale)
{
    _sprite.setScale(_scale);
}

const sf::Sprite& Sprite::getSprite() const
{
    return _sprite;
}

void Sprite::setTextureRect(int x, int y, int width, int height)
{
    _sprite.setTextureRect(sf::IntRect(sf::Vector2i(x, y), sf::Vector2i(width, height)));
};

const sf::Vector2f &Sprite::getScale() const
{
    return _scale;
}
}
