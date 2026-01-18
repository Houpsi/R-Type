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
        for (auto const &entity : ecs.getEntitiesWithComponent<InputPlayer>()) {
            auto pos = entity->getComponent<Position>();
            auto input = entity->getComponent<InputPlayer>();
            auto velocity = entity->getComponent<Velocity>();
            float dirX = 0.0f;
            float dirY = 0.0f;

            if (input->getUp()) {
                dirY += ecs::dir::up;
            }
            if (input->getDown()) {
                dirY += ecs::dir::down;
            }
            if (input->getLeft()) {
                dirX += ecs::dir::left;
            }
            if (input->getRight()) {
                dirX += ecs::dir::right;
            }
            velocity->setDirection({dirX, dirY});
        }
    }
}
