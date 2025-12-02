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

    [[nodiscard]] TypeCollision GetTypeCollision() const;
    void SetTypeCollision(TypeCollision typeCollision);

    [[nodiscard]] bool GetIsTrigger() const;
    void SetIsTrigger(bool isTrigger);

    [[nodiscard]] float GetHeight() const;
    void SetHeight(float height);

    [[nodiscard]] float GetLength() const;
    void SetLength(float length);

  private:
    TypeCollision _typeCollision;
    bool _isTrigger = false;
    float _height;
    float _length;
};
}

#endif //BOOTSTRAP_COLLIDER_HPP