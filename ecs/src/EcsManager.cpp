/*
** EPITECH PROJECT, 2025
** r-type_client
** File description:
** EcsManager
*/

#include "EcsManager.hpp"
#include <memory>
#include "Entity.hpp"
#include "ResourceManager.hpp"

namespace ecs {
    std::shared_ptr<Entity> EcsManager::createEntity() {
        auto entity = std::make_shared<Entity>(_nextEntityId);
        _entities.push_back(entity);
        _nextEntityId++;
        return entity;
    }

    std::shared_ptr<Entity> EcsManager::createEntity(std::size_t id)
    {
        auto entity = std::make_shared<Entity>(id);
        _entities.push_back(entity);
        return entity;
    }

    std::vector<std::shared_ptr<Entity>> &EcsManager::getEntities() {
        return _entities;
    }

    void EcsManager::setDeltaTime(float dt)
    {
        _deltaTime = dt;
    }
    float EcsManager::getDeltaTime() const
    {
        return _deltaTime;
    }

    void EcsManager::updateSystems() {
        for (const auto& system : _systems) {
            system->update(*this);
        }
    }

    ResourceManager &EcsManager::getResourceManager()
    {
        return _resourceManager;
    }

    std::shared_ptr<Entity> EcsManager::getEntityById(uint64_t id) const
    {
        for (const auto& entity : _entities) {
            if (entity->getId() == id) {
                return entity;
            }
        }
        return nullptr;
    }
}