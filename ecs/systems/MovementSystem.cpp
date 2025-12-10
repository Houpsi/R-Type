/*
** EPITECH PROJECT, 2025
** R_Type
** File description:
** MovementSystem
*/

#include "MovementSystem.hpp"

namespace ecs {
void MovementSystem::update(EcsManager &ecs)
{
    const float speed = 250.f;
    const float dt = ecs.getDeltaTime();
    for (auto const &entity : ecs.getEntitiesWithComponent<InputPlayer>()) {
        auto pos = entity->getComponent<Position>();
        auto input = entity->getComponent<InputPlayer>();
        if (input) {
            if (input->getUp())
                pos->setY(pos->getY() - (speed * dt));
            if (input->getDown())
                pos->setY(pos->getY() + (speed * dt));
            if (input->getLeft())
                pos->setX(pos->getX() - (speed * dt));
            if (input->getRight())
                pos->setX(pos->getX() + (speed * dt));
        }
    }
    for (auto const &enemy : ecs.getEntitiesWithComponent<Enemy>()) {
        auto pos = enemy->getComponent<Position>();
        if (pos) {
            pos->setX(pos->getX() + (-speed * dt));
        }
    }
}
}
