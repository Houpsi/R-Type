/*
** EPITECH PROJECT, 2025
** R_Type
** File description:
** MovementSystem
*/


#ifndef MOVEMENTSYSTEM_HPP
    #define MOVEMENTSYSTEM_HPP
#include "../system/System.hpp"
#include "managers/EcsManager.hpp"
#include "components/position/Position.hpp"
#include "components/enemy/Enemy.hpp"
#include "components/inputPlayer/InputPlayer.hpp"
#include "components/collision/Collision.hpp"
#include "components/destroy/Destroy.hpp"

namespace ecs {
class MovementSystem : public System
{
  public:
    explicit MovementSystem(): _movementSpeed(10) {};
    ~MovementSystem() override = default;
    void update(EcsManager &ecs) override;
  private:
    float _movementSpeed;
};
}


#endif //MOVEMENTSYSTEM_HPP