/*
** EPITECH PROJECT, 2025
** r-type_client
** File description:
** ShootSystem
*/

#ifndef R_TYPE_CLIENT_SHOOTSYSTEM_HPP
    #define R_TYPE_CLIENT_SHOOTSYSTEM_HPP
#include "systems/system/ASystem.hpp"
#include "components/shoot/Shoot.hpp"
#include "components/inputPlayer/InputPlayer.hpp"
#include "managers/EcsManager.hpp"
#include "components/position/Position.hpp"
#include "components/collision/Collision.hpp"
#include "components/sprite/Sprite.hpp"
#include "components/velocity/Velocity.hpp"
#include "components/animation/Animation.hpp"

namespace ecs {
class ShootSystem : public ASystem {
  public:
    ShootSystem() = default;
    void update(EcsManager &ecs) override;
};
}

#endif// R_TYPE_CLIENT_SHOOTSYSTEM_HPP
