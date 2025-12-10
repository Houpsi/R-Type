/*
** EPITECH PROJECT, 2025
** r-type_client
** File description:
** CollisionSystem
*/

#include "CollisionSystem.hpp"

namespace ECS {

/**
 * Check if the entity can have a collision, and is there is one
 * check if there is a collision with an another entity
 * @param ecs
 */
void CollisionSystem::update(ECS::EcsManager &ecs)
{
    for (auto& entity: ecs.getEntities()) {
        auto collision = entity->getComponent<Collision>();
        if (!collision) continue;
        auto pos = entity->getComponent<Position>();
        auto X = pos->getX();
        auto Y = pos->getY();
        auto height = collision->getHeight();
        auto length = collision->getWidth();

        for (auto otherEntity: ecs.getEntities()) {
            if (entity == otherEntity) continue;
            auto otherCollision = otherEntity->getComponent<Collision>();
            auto posOtherEntity = otherEntity->getComponent<Position>();

            if (collision->getTypeCollision() == ECS::TypeCollision::PLAYER && otherCollision->getTypeCollision() == ECS::TypeCollision::PLAYER) continue;
            if (collision->getTypeCollision() == ECS::TypeCollision::ENEMY && otherCollision->getTypeCollision() == ECS::TypeCollision::OBSTACLE) continue;
            if (collision->getTypeCollision() == ECS::TypeCollision::PLAYER && otherCollision->getTypeCollision() == ECS::TypeCollision::PLAYER_PROJECTILE) continue;
            if (collision->getTypeCollision() == ECS::TypeCollision::ENEMY && otherCollision->getTypeCollision() == ECS::TypeCollision::ENEMY_PROJECTILE) continue;
            if (collision->getTypeCollision() == ECS::TypeCollision::ENEMY && otherCollision->getTypeCollision() == ECS::TypeCollision::ENEMY) continue;

            if (X < (posOtherEntity->getX() + otherCollision->getWidth()) &&
                (X + length) > posOtherEntity->getX() &&
                Y < (posOtherEntity->getY() + otherCollision->getHeight()) &&
                (Y + collision->getHeight()) > posOtherEntity->getY()
                ) {
                std::cout << "COLLLLISION !!!!" << std::endl;
                collision->setIsTrigger(true);
                otherCollision->setIsTrigger(true);
            }
        }
    }
}

}