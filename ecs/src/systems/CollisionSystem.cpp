/*
** EPITECH PROJECT, 2025
** r-type_client
** File description:
** CollisionSystem
*/

#include "CollisionSystem.hpp"

#include "components/Sound.hpp"

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
            auto position  = entity->getComponent<Position>();

            if (!collision || !position)
                continue;

            const float x = position->getX();
            const float y = position->getY();
            const float width  = collision->getWidth();
            const float height = collision->getHeight();

            for (const auto &other : entities) {
                if (entity == other)
                    continue;

                auto otherCollision = other->getComponent<Collision>();
                auto otherPosition  = other->getComponent<Position>();

                if (!otherCollision || !otherPosition)
                    continue;

                if (shouldIgnoreCollision(
                        collision->getTypeCollision(),
                        otherCollision->getTypeCollision()))
                    continue;

                const float ox = otherPosition->getX();
                const float oy = otherPosition->getY();
                const float oWidth  = otherCollision->getWidth();
                const float oHeight = otherCollision->getHeight();

                if (!isColliding(x, y, width, height, ox, oy, oWidth, oHeight))
                    continue;

                collision->setIsTrigger(true);
                otherCollision->setIsTrigger(true);

                const auto typeA = collision->getTypeCollision();
                const auto typeB = otherCollision->getTypeCollision();

                if (typeA == TypeCollision::PLAYER_PROJECTILE &&
                    typeB == TypeCollision::ENEMY) {

                    auto health = other->getComponent<Health>();
                    auto shoot  = entity->getComponent<Shoot>();

                    if (health && shoot)
                        health->setHealth(health->getHealth() - shoot->getDamage());
                    entity->addComponent<Sound>(1, false);
                    entity->addComponent<Destroy>();
                }

                if (typeA == TypeCollision::PLAYER &&
                    typeB == TypeCollision::ENEMY) {
                    entity->addComponent<Sound>(1, false);
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