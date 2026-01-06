/*
** EPITECH PROJECT, 2025
** R_Type
** File description:
** EntityManager
*/


#include "EntityManager.hpp"

namespace ecs {
    Entity EntityManager::createEntity()
    {
        if (!_availableEntities.empty()) {
            Entity newEntity = _availableEntities.front();
            _availableEntities.pop();
            return newEntity;
        }
        _livingEntityCount++;
        return _livingEntityCount;
    }

    void EntityManager::deleteEntity(Entity id)
    {
        _signatures[id].reset();
        _availableEntities.push(id);
    }

}
