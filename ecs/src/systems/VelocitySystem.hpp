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
#include "components/Velocity.hpp"
#include "components/Position.hpp"
#include "components/Enemy.hpp"
#include "components/InputPlayer.hpp"
#include "components/Collision.hpp"
#include "components/Destroy.hpp"

namespace ecs {
class VelocitySystem : public System {
public:
    explicit VelocitySystem() = default;
    ~VelocitySystem() override = default;
    void update(EcsManager &ecs) override;
};
}


#endif //R_TYPE_CLIENT_VELOCITYSYSTEM_HPP
