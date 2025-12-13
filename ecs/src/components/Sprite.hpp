/*
** EPITECH PROJECT, 2025
** R_Type
** File description:
** Sprite
*/

#ifndef R_TYPE_SPRITE_HPP
    #define R_TYPE_SPRITE_HPP
#include "Component.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>

namespace ecs {
class Sprite : public Component
{
  public:
    explicit Sprite(sf::Texture &texture) : _sprite(texture) {}
    ~Sprite() override = default;
    const sf::Sprite &getSprite() const;
    void setTextureRect(int x, int y, int width, int height);
  private:
    sf::Sprite _sprite;
};
}

#endif //R_TYPE_SPRITE_HPP
