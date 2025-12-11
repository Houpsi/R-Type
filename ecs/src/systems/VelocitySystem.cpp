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
        for (auto const &entity : ecs.getEntitiesWithComponent<Velocity>()) {
            auto pos = entity->getComponent<Position>();
            auto direction = entity->getComponent<Velocity>()->getDirection();
            auto velocity = entity->getComponent<Velocity>()->getVelocity();
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
