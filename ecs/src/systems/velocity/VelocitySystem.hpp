/*
** EPITECH PROJECT, 2025
** r-type_client
** File description:
** VelocitySystem
*/

#ifndef R_TYPE_CLIENT_VELOCITYSYSTEM_HPP
    #define R_TYPE_CLIENT_VELOCITYSYSTEM_HPP
#include "managers/EcsManager.hpp"
#include "systems/system/ASystem.hpp"
#include "components/velocity/Velocity.hpp"
#include "components/position/Position.hpp"

namespace ecs {
    class VelocitySystem : public ASystem {
    public:
        ~VelocitySystem() override = default;
        void update(EcsManager &ecs) override;
        void configure(EcsManager &ecs) override;
    };
}


#endif //R_TYPE_CLIENT_VELOCITYSYSTEM_HPP
