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
        for (auto const &entity : _entity) {
            auto pos = ecs.getComponentManager()<Position>->get(entity);
            auto direction = ecs.getComponentManager()<Velocity>->get(entity)->getDirection();
            auto velocity = ecs.getComponentManager()<Velocity>->get(entity)->getVelocity();

            if (direction == 0) {
                pos->setX(pos->getX() - (velocity * dt));
            }
            if (direction == 1) {
                pos->setX(pos->getX() + (velocity * dt));
            }
            if (direction == 2) {
                pos->setY(pos->getY() - (velocity * dt));
            }
            if (direction == 3) {
                pos->setY(pos->getY() + (velocity * dt));
            }
        }
    }
}
