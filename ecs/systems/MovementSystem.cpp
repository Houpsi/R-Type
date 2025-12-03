/*
** EPITECH PROJECT, 2025
** R_Type
** File description:
** MovementSystem
*/

#include "MovementSystem.hpp"
#include "EcsManager.hpp"
#include "Position.hpp"
#include "Enemy.hpp"
#include "InputPlayer.hpp"

namespace ECS {
void MovementSystem::update(EcsManager &ecs)
{
    float speed = 250.f;
    float dt = ecs.deltaTime();
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
