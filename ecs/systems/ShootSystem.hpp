/*
** EPITECH PROJECT, 2025
** r-type_client
** File description:
** ShootSystem
*/

#ifndef R_TYPE_CLIENT_SHOOTSYSTEM_HPP
#define R_TYPE_CLIENT_SHOOTSYSTEM_HPP

#include "System.hpp"
#include "Shoot.hpp"
#include "InputPlayer.hpp"
#include "EcsManager.hpp"
#include "Position.hpp"
#include "Collision.hpp"
#include "Sprite.hpp"

namespace ECS {
class ShootSystem : public System {
  public:
    ShootSystem() = default;
    void update(EcsManager &ecs) override;
};
}


#endif// R_TYPE_CLIENT_SHOOTSYSTEM_HPP
