/*
** EPITECH PROJECT, 2025
** r-type_client
** File description:
** CollisionSystem
*/

#ifndef BOOTSTRAP_COLLISIONSYSTEM_HPP
    #define BOOTSTRAP_COLLISIONSYSTEM_HPP
#include "components/Sprite.hpp"
#include "EcsManager.hpp"
#include "components/Collision.hpp"
#include "components/Position.hpp"

namespace ecs {
class CollisionSystem: public System {
  public:
    CollisionSystem() = default;
    void update(EcsManager &ecs) override;
    static bool shouldIgnoreCollision(TypeCollision a, TypeCollision b);
    static bool isColliding( float x1, float y1, float w1, float h1,
		float x2, float y2, float w2, float h2);
};
}

#endif //BOOTSTRAP_COLLISIONSYSTEM_HPP