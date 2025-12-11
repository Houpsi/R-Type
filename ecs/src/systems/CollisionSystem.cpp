/*
** EPITECH PROJECT, 2025
** r-type_client
** File description:
** CollisionSystem
*/

#include "CollisionSystem.hpp"

namespace ecs {

/**
 * Check if the entity can have a collision, and is there is one
 * check if there is a collision with an another entity
 * @param ecs
 */
void CollisionSystem::update(ecs::EcsManager &ecs)
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

            if (collision->getTypeCollision() == ecs::TypeCollision::PLAYER && otherCollision->getTypeCollision() == ecs::TypeCollision::PLAYER) continue;
            if (collision->getTypeCollision() == ecs::TypeCollision::ENEMY && otherCollision->getTypeCollision() == ecs::TypeCollision::OBSTACLE) continue;
            if (collision->getTypeCollision() == ecs::TypeCollision::PLAYER && otherCollision->getTypeCollision() == ecs::TypeCollision::PLAYER_PROJECTILE) continue;
            if (collision->getTypeCollision() == ecs::TypeCollision::ENEMY && otherCollision->getTypeCollision() == ecs::TypeCollision::ENEMY_PROJECTILE) continue;
            if (collision->getTypeCollision() == ecs::TypeCollision::ENEMY && otherCollision->getTypeCollision() == ecs::TypeCollision::ENEMY) continue;

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