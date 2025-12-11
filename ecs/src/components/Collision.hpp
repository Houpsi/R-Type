/*
** EPITECH PROJECT, 2025
** r-type_client
** File description:
** Collision
*/

#ifndef BOOTSTRAP_COLLIDER_HPP
    #define BOOTSTRAP_COLLIDER_HPP
#include "Component.hpp"
#include <SFML/Graphics/Sprite.hpp>

namespace ecs {
    enum TypeCollision {
        PLAYER,
        ENEMY,
        PLAYER_PROJECTILE,
        ENEMY_PROJECTILE,
        OBSTACLE,
    };

class Collision: public Component {
  public:
    explicit Collision(TypeCollision typeColision, float height, float width): _typeCollision(typeColision), _height(height), _width(width) {};
    ~Collision() = default;

    [[nodiscard]] TypeCollision getTypeCollision() const;
    void setTypeCollision(TypeCollision typeCollision);

    [[nodiscard]] bool getIsTrigger() const;
    void setIsTrigger(bool isTrigger);

    [[nodiscard]] float getHeight() const;
    void setHeight(float height);

    [[nodiscard]] float getWidth() const;
    void setWidth(float width);

  private:
    TypeCollision _typeCollision;
    bool _isTrigger = false;
    float _height;
    float _width;
};
}

#endif //BOOTSTRAP_COLLIDER_HPP