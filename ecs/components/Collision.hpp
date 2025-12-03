/*
** EPITECH PROJECT, 2025
** r-type_client
** File description:
** Collision
*/

#ifndef BOOTSTRAP_COLLIDER_HPP
#define BOOTSTRAP_COLLIDER_HPP

#include <SFML/Graphics/Sprite.hpp>
#include "Component.hpp"


namespace ECS {
    enum TypeCollision {
        PLAYER,
        ENEMY,
        PLAYER_BULLET,
        ENEMY_BULLET,
        OBSTACLE,
    };

class Collision: public Component {
  public:
    explicit Collision(TypeCollision typeColision, float height, float length): _typeCollision(typeColision), _height(height), _length(length) {};
    ~Collision() = default;

    [[nodiscard]] TypeCollision getTypeCollision() const;
    void setTypeCollision(TypeCollision typeCollision);

    [[nodiscard]] bool getIsTrigger() const;
    void setIsTrigger(bool isTrigger);

    [[nodiscard]] float getHeight() const;
    void setHeight(float height);

    [[nodiscard]] float getLength() const;
    void setLength(float length);

  private:
    TypeCollision _typeCollision;
    bool _isTrigger = false;
    float _height;
    float _length;
};
}

#endif //BOOTSTRAP_COLLIDER_HPP