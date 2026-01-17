/*
** EPITECH PROJECT, 2025
** r-type_client
** File description:
** Health
*/

#include "HealthSystem.hpp"
#include "EcsConstant.hpp"
#include "components/Collision.hpp"
#include "components/Score.hpp"

namespace ecs
{
    void HealthSystem::update(EcsManager& ecs)
    {
        for (auto& entity : ecs.getEntitiesWithComponent<ecs::Health>())
        {
            auto health = entity->getComponent<ecs::Health>();
            auto collision = entity->getComponent<ecs::Collision>();

            if (health->getHealth() <= 0) {
                if (collision && collision->getTypeCollision() == ENEMY) {
                    auto scoreEntities = ecs.getEntitiesWithComponent<ecs::Score>();
                    for (auto& scoreEntity : scoreEntities) {
                        auto score = scoreEntity->getComponent<ecs::Score>();
                        if (!score) continue;
                        score->addToScore(ecs::scoreKillMonster);
                    }
                }
                entity->addComponent<ecs::Destroy>();
            }
        }

    }
} // ecs