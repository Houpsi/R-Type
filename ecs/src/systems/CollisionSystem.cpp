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
            if (!collision || !entity->getComponent<Position>()) continue;
            auto pos = entity->getComponent<Position>();
            auto X = pos->getX();
            auto Y = pos->getY();
            auto height = collision->getHeight() * entity->getComponent<Sprite>()->getScale().x;
            auto length = collision->getWidth() * entity->getComponent<Sprite>()->getScale().y;

            for (auto otherEntity: ecs.getEntities()) {
                if (!otherEntity->getComponent<Collision>() || !otherEntity->getComponent<Position>()) continue;
                if (entity == otherEntity) continue;
                auto otherCollision = otherEntity->getComponent<Collision>();
                auto posOtherEntity = otherEntity->getComponent<Position>();

                if (collision->getTypeCollision() == ecs::TypeCollision::PLAYER && otherCollision->getTypeCollision() == ecs::TypeCollision::PLAYER) continue;
                if (collision->getTypeCollision() == ecs::TypeCollision::ENEMY && otherCollision->getTypeCollision() == ecs::TypeCollision::OBSTACLE) continue;
                if (collision->getTypeCollision() == ecs::TypeCollision::PLAYER && otherCollision->getTypeCollision() == ecs::TypeCollision::PLAYER_PROJECTILE) continue;
                if (collision->getTypeCollision() == ecs::TypeCollision::PLAYER_PROJECTILE && otherCollision->getTypeCollision() == ecs::TypeCollision::PLAYER) continue;
                if (collision->getTypeCollision() == ecs::TypeCollision::ENEMY && otherCollision->getTypeCollision() == ecs::TypeCollision::ENEMY_PROJECTILE) continue;
                if (collision->getTypeCollision() == ecs::TypeCollision::ENEMY && otherCollision->getTypeCollision() == ecs::TypeCollision::ENEMY) continue;
                if (collision->getTypeCollision() == ecs::TypeCollision::ENEMY && otherCollision->getTypeCollision() == ecs::TypeCollision::PLAYER_PROJECTILE) continue;
                if (collision->getTypeCollision() == ecs::TypeCollision::ENEMY && otherCollision->getTypeCollision() == ecs::TypeCollision::PLAYER) continue;

                if (X < (posOtherEntity->getX() + (otherCollision->getWidth() * otherEntity->getComponent<Sprite>()->getScale().x)) &&
                    (X + length) > posOtherEntity->getX() &&
                    Y < (posOtherEntity->getY() + (otherCollision->getHeight() * otherEntity->getComponent<Sprite>()->getScale().x)) &&
                    (Y + height) > posOtherEntity->getY()
                ) {
                    otherCollision->setIsTrigger(true);
                    collision->setIsTrigger(true);
                    const auto& typeCollisionFirstEntity = collision->getTypeCollision();
                    const auto& typeCollisionSecondEntity = otherCollision->getTypeCollision();
                    if (typeCollisionFirstEntity == ecs::TypeCollision::PLAYER_PROJECTILE && typeCollisionSecondEntity == ecs::TypeCollision::ENEMY)
                    {
                        otherEntity->getComponent<Health>()->setHealth(otherEntity->getComponent<Health>()->getHealth() - entity->getComponent<Shoot>()->getDamage());
                        entity->addComponent<Destroy>();
                    }
                    if (typeCollisionFirstEntity == ecs::TypeCollision::PLAYER && typeCollisionSecondEntity == ecs::TypeCollision::ENEMY)
                    {
                        entity->addComponent<Destroy>();
                    }
                }
            }
        }
    }

}