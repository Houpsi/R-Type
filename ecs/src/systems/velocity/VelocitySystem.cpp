/*
** EPITECH PROJECT, 2025
** r-type_client
** File description:
** VelocitySystem
*/

#include "VelocitySystem.hpp"

namespace ecs {

    void VelocitySystem::update(EcsManager &ecs)
    {
        float dt = ecs.getDeltaTime();
        for (auto const &entity : _entities) {
            auto pos = ecs.getComponent<Position>(entity);
            auto direction = ecs.getComponent<Velocity>(entity).getDirection();
            auto velocity = ecs.getComponent<Velocity>(entity).getVelocity();

            if (direction == 0) {
                pos.setX(pos.getX() - (velocity * dt));
            }
            if (direction == 1) {
                pos.setX(pos.getX() + (velocity * dt));
            }
            if (direction == 2) {
                pos.setY(pos.getY() - (velocity * dt));
            }
            if (direction == 3) {
                pos.setY(pos.getY() + (velocity * dt));
            }
        }
    }

    void VelocitySystem::configure(EcsManager &ecs)
    {
        _targetSignature.set(ecs.getComponentType<Position>());
        _targetSignature.set(ecs.getComponentType<Velocity>());
    }
}
