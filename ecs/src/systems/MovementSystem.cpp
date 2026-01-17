/*
** EPITECH PROJECT, 2025
** R_Type
** File description:
** MovementSystem
*/

#include "MovementSystem.hpp"
#include "components/Velocity.hpp"
#include "EcsConstant.hpp"
#include <iostream>

namespace ecs {
    void MovementSystem::update(EcsManager &ecs)
    {
        constexpr uint16_t windowWidth = 1920;

        const float speed = 250.0F;
        const float dt = ecs.getDeltaTime();
        for (auto const &entity : ecs.getEntitiesWithComponent<InputPlayer>()) {
            auto pos = entity->getComponent<Position>();
            auto input = entity->getComponent<InputPlayer>();

            if (input) {
                if (input->getUp()) {
                    pos->setY(pos->getY() - (speed * dt));
                }
                if (input->getDown()) {
                    pos->setY(pos->getY() + (speed * dt));
                }
                if (input->getLeft()) {
                    pos->setX(pos->getX() - (speed * dt));
                }
                if (input->getRight()) {
                    pos->setX(pos->getX() + (speed * dt));
                }
            }
        }
    }
}
