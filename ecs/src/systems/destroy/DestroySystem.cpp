/*
** EPITECH PROJECT, 2025
** r-type_client
** File description:
** DestroySystem
*/

#include "DestroySystem.hpp"
#include "components/destroy/Destroy.hpp"

namespace ecs {

void DestroySystem::update(EcsManager &ecs)
{
    // auto &entities = ecs.getEntities();

    std::erase_if(_entity, [&ecs](Entity entity) {
        auto &destroy = ecs.getComponentManager().getComponent<Destroy>(entity);
        return true;
    });


    // std::erase_if(entities, [](std::shared_ptr<Entity> &entity) {
        // return entity->getComponent<Destroy>();
    // });
}

}