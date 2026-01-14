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

    Entity EntityManager::createEntity(std::size_t id)
    {
        if (!_availableEntities.empty()) {
            Entity newEntity = id;
            _availableEntities.pop();
            return newEntity;
        }
        _livingEntityCount++;
        return _livingEntityCount;
    }

    void EntityManager::deleteEntity(Entity id)
    {
        if (id >= cmn::MAX_ENTITIES) {
            return;
        }
        _signatures.at(id).reset();
        _availableEntities.push(id);
    }

    void EntityManager::setSignature(Entity entity, Signature newSignature)
    {
        if (entity >= cmn::MAX_ENTITIES) {
            return;
        }
        _signatures.at(entity) = newSignature;
    }

    Signature EntityManager::getSignature(Entity entity)
    {
        if (entity >= cmn::MAX_ENTITIES) {
            return {};
        }
        return _signatures.at(entity);
    }

    std::queue<Entity> EntityManager::getAvailableEntities() const
    {
        return _availableEntities;
    }
}
