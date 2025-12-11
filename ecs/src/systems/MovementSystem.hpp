/*
** EPITECH PROJECT, 2025
** R_Type
** File description:
** MovementSystem
*/


#ifndef MOVEMENTSYSTEM_HPP
    #define MOVEMENTSYSTEM_HPP
#include "System.hpp"
#include "EcsManager.hpp"
#include "components/Position.hpp"
#include "components/Enemy.hpp"
#include "components/InputPlayer.hpp"
#include "components/Collision.hpp"
#include "components/Destroy.hpp"

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