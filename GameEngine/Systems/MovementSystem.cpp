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

void MovementSystem::update(EcsManager &ecs)
{
    float speed = 150.f;
    float dt = ecs.deltaTime();
    for (auto entity : ecs.getEntitiesWithComponent<InputPlayer>()) {
        auto pos = entity->getComponent<Position>();
        auto input = entity->getComponent<InputPlayer>();
        if (input)
        {
            if (input->getDown())
                pos->setX(pos->getX() + (speed * dt));
        }
    }
    for (auto enemy : ecs.getEntitiesWithComponent<Enemy>())
    {
        auto pos = enemy->getComponent<Position>();
        if (pos)
        {
            pos->setX(pos->getX() + (speed * dt));
        }
    }
}
