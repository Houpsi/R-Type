/*
** EPITECH PROJECT, 2025
** r-type_client
** File description:
** CollisionSystem
*/

#include "CollisionSystem.hpp"

namespace ecs
{
    /**
    * Check if the entity can have a collision, and is there is one
    * check if there is a collision with another entity
    * @param ecs
    */
    void CollisionSystem::update(EcsManager &ecs)
    {
        const auto &entities = ecs.getEntities();

        for (const auto &entity : entities) {
            auto collision = entity->getComponent<Collision>();
            if (!collision || !entity->getComponent<Position>()) continue;
            auto pos = entity->getComponent<Position>();
            auto X = pos->getX();
            auto Y = pos->getY();
            auto height = collision->getHeight();
            auto length = collision->getWidth();

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

                if (X < (posOtherEntity->getX() + (otherCollision->getWidth())) &&
                    (X + length) > posOtherEntity->getX() &&
                    Y < (posOtherEntity->getY() + (otherCollision->getHeight())) &&
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

                if (typeA == TypeCollision::PLAYER &&
                    typeB == TypeCollision::ENEMY) {

                    entity->addComponent<Destroy>();
                    }
            }
        }
    }

    bool CollisionSystem::shouldIgnoreCollision(const TypeCollision a, const TypeCollision b)
    {
        if (a == TypeCollision::PLAYER && b == TypeCollision::PLAYER)
            return true;
        if (a == TypeCollision::ENEMY && b == TypeCollision::OBSTACLE)
            return true;
        if (a == TypeCollision::PLAYER && b == TypeCollision::PLAYER_PROJECTILE)
            return true;
        if (a == TypeCollision::PLAYER_PROJECTILE && b == TypeCollision::PLAYER)
            return true;
        if (a == TypeCollision::ENEMY && b == TypeCollision::ENEMY_PROJECTILE)
            return true;
        if (a == TypeCollision::ENEMY && b == TypeCollision::ENEMY)
            return true;
        if (a == TypeCollision::ENEMY && b == TypeCollision::PLAYER_PROJECTILE)
            return true;
        if (a == TypeCollision::ENEMY && b == TypeCollision::PLAYER)
            return true;

        return false;
    }

    bool CollisionSystem::isColliding(
        float x1, float y1, float w1, float h1,
        float x2, float y2, float w2, float h2)
    {
        return x1 < x2 + w2 &&
            x1 + w1 > x2 &&
            y1 < y2 + h2 &&
            y1 + h1 > y2;
    }
}