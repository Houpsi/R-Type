/*
** EPITECH PROJECT, 2025
** r-type_client
** File description:
** VelocitySystem
*/

#ifndef R_TYPE_CLIENT_VELOCITYSYSTEM_HPP
#define R_TYPE_CLIENT_VELOCITYSYSTEM_HPP

#include "EcsManager.hpp"
#include "System.hpp"
#include "Velocity.hpp"
#include "Position.hpp"

namespace ECS {
class VelocitySystem : public System {
public:
    explicit VelocitySystem() = default;
    ~VelocitySystem() override = default;
    void update(EcsManager &ecs) override;
};
}


#endif //R_TYPE_CLIENT_VELOCITYSYSTEM_HPP
