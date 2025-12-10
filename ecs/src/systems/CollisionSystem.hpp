/*
** EPITECH PROJECT, 2025
** r-type_client
** File description:
** CollisionSystem
*/

#ifndef BOOTSTRAP_COLLISIONSYSTEM_HPP
    #define BOOTSTRAP_COLLISIONSYSTEM_HPP
#include "Sprite.hpp"
#include "EcsManager.hpp"
#include "Collision.hpp"
#include "Position.hpp"

namespace ecs {
class CollisionSystem: public System {
  public:
    CollisionSystem() = default;
    void update(EcsManager &ecs) override;
};
}

#endif //BOOTSTRAP_COLLISIONSYSTEM_HPP