/*
** EPITECH PROJECT, 2025
** r-type_client
** File description:
** ShootSystem
*/

#ifndef R_TYPE_CLIENT_SHOOTSYSTEM_HPP
    #define R_TYPE_CLIENT_SHOOTSYSTEM_HPP
#include "System.hpp"
#include "components/Shoot.hpp"
#include "components/InputPlayer.hpp"
#include "EcsManager.hpp"
#include "components/Position.hpp"
#include "components/Collision.hpp"
#include "components/Sprite.hpp"
#include "components/Velocity.hpp"
#include "components/Animation.hpp"

namespace ecs {
class ShootSystem : public System {
  public:
    ShootSystem() = default;
    void update(EcsManager &ecs) override;
};
}

#endif// R_TYPE_CLIENT_SHOOTSYSTEM_HPP
