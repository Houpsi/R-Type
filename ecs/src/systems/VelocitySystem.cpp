/*
** EPITECH PROJECT, 2025
** r-type_client
** File description:
** VelocitySystem
*/

#include "VelocitySystem.hpp"
#include "EcsConstant.hpp"

namespace ecs {

    void VelocitySystem::update(EcsManager &ecs)
    {
        float dt = ecs.getDeltaTime();
        for (auto const &entity : ecs.getEntitiesWithComponent<Velocity>()) {
            auto pos = entity->getComponent<Position>();
            auto direction = entity->getComponent<Velocity>()->getDirection();
            auto velocity = entity->getComponent<Velocity>()->getVelocity();
            auto collision = entity->getComponent<Collision>();

            if (pos) {
                pos->setX(pos->getX() + (direction.first * velocity * dt));
                pos->setY(pos->getY() + (direction.second * velocity * dt));
                if (collision) {
                    if (pos->getX() < 0 - entity->getComponent<Collision>()->getWidth()) {
                        entity->addComponent<Destroy>();
                    }
                    if (pos->getX() > ecs::windowWidth + entity->getComponent<Collision>()->getWidth() + 500) {
                        entity->addComponent<Destroy>();
                    }
                }
            }
        }
    }
}
