/*
** EPITECH PROJECT, 2025
** r-type_client
** File description:
** VelocitySystem
*/

#include "VelocitySystem.hpp"
#include "src/Constants.hpp"

namespace ecs {

    void VelocitySystem::update(EcsManager &ecs)
    {
        float dt = ecs.getDeltaTime();
        for (auto const &entity : ecs.getEntitiesWithComponent<Velocity>()) {
            auto pos = entity->getComponent<Position>();
            auto direction = entity->getComponent<Velocity>()->getDirection();
            auto velocity = entity->getComponent<Velocity>()->getVelocity();
            auto collision = entity->getComponent<Collision>();

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
            if (collision) {
                if (pos->getX() < 0 - entity->getComponent<Collision>()->getWidth()) {
                    entity->addComponent<Destroy>();
                }
                if (pos->getX() > cmn::windowWidth + entity->getComponent<Collision>()->getWidth() + 500) {
                    entity->addComponent<Destroy>();
                }
            }
        }
    }
}
