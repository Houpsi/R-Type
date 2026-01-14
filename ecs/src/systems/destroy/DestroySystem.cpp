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
        ecs.destroyEntities(_entities);
    }

    void DestroySystem::configure(EcsManager &ecs)
    {
        _targetSignature.set(ecs.getComponentType<Destroy>());
    }
}