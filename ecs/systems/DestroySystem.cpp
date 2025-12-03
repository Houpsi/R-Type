/*
** EPITECH PROJECT, 2025
** r-type_client
** File description:
** DestroySystem
*/

#include "DestroySystem.hpp"
#include "Destroy.hpp"

namespace ECS {

void DestroySystem::update(EcsManager &ecs)
{
    auto &entities = ecs.getEntities();

    erase_if(entities, [](std::shared_ptr<Entity> &entity) {
        return entity->getComponent<Destroy>();
    });
}

}