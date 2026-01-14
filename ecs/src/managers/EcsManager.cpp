/*
** EPITECH PROJECT, 2025
** r-type_client
** File description:
** EcsManager
*/

#include "EcsManager.hpp"
#include "ComponentManager.hpp"
#include "EntityManager.hpp"
#include "ResourceManager.hpp"
#include "SystemManager.hpp"

namespace ecs {

    ResourceManager& EcsManager::getResourceManager()
    {
        return _resourceManager;
    }

    void EcsManager::setDeltaTime(float dt)
    {
        _deltaTime = dt;
    }
    float EcsManager::getDeltaTime() const
    {
        return _deltaTime;
    }

    void EcsManager::destroyEntities(std::vector<ecs::Entity> &entitiesToDestroy)
    {
        for (auto &entity : entitiesToDestroy) {
            _componentManager.entityDestroyed(entity);
            _entityManager.deleteEntity(entity);
        }
        entitiesToDestroy.clear();
    }

    Entity EcsManager::createEntity()
    {
        return _entityManager.createEntity();
    }

    void EcsManager::deleteEntity(Entity entity)
    {
        _componentManager.entityDestroyed(entity);
        _entityManager.deleteEntity(entity);
    }
}