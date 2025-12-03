/*
** EPITECH PROJECT, 2025
** r-type_client
** File description:
** CollisionSystem
*/

#include "CollisionSystem.hpp"

namespace ECS {
void CollisionSystem::update(ECS::EcsManager &ecs)
{
    for (auto& entity: ecs.getEntities()) {
        auto collision = entity->getComponent<Collision>();
        if (!collision) continue;
        auto pos = entity->getComponent<Position>();
        auto X = pos->getX();
        auto Y = pos->getY();
        auto height = collision->getHeight();
        auto length = collision->getLength();

        for (auto entity2: ecs.getEntities()) {
            if (entity == entity2) continue;
            auto collision2 = entity2->getComponent<Collision>();
            auto pos2 = entity2->getComponent<Position>();

            if (collision->getTypeCollision() == ECS::TypeCollision::PLAYER && collision2->getTypeCollision() == ECS::TypeCollision::PLAYER) continue;
            if (collision->getTypeCollision() == ECS::TypeCollision::ENEMY && collision2->getTypeCollision() == ECS::TypeCollision::OBSTACLE) continue;
            if (collision->getTypeCollision() == ECS::TypeCollision::PLAYER && collision2->getTypeCollision() == ECS::TypeCollision::PLAYER_BULLET) continue;
            if (collision->getTypeCollision() == ECS::TypeCollision::ENEMY && collision2->getTypeCollision() == ECS::TypeCollision::ENEMY_BULLET) continue;
            if (collision->getTypeCollision() == ECS::TypeCollision::ENEMY && collision2->getTypeCollision() == ECS::TypeCollision::ENEMY) continue;

            if (X < (pos2->getX() + collision2->getLength()) &&
                (X + length) > pos2->getX() &&
                Y < (pos2->getY() + collision2->getHeight()) &&
                (Y + collision->getHeight()) > pos2->getY()
                ) {
                std::cout << "COLLLLISION !!!!" << std::endl;
                collision->setIsTrigger(true);
                collision2->setIsTrigger(true);
            }
        }
    }
}

}