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
//        auto tmp = entity->getComponent<Position>()

    }
}

}