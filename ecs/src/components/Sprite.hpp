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
    explicit Sprite(const std::string &texturePath, sf::Vector2f scale);
    ~Sprite() override = default;
    const sf::Sprite &getSprite() const;
    void setTextureRect(int x, int y, int width, int height);
	sf::Vector2f getScale() const;

  private:
    sf::Sprite _sprite;
    sf::Texture _texture;
	sf::Vector2f _scale;
};
}

#endif //R_TYPE_SPRITE_HPP
