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

    EntityManager &EcsManager::getEntityManager()
    {
        return _entityManager;
    }

    ComponentManager &EcsManager::getComponentManager()
    {
        return _componentManager;
    }

    SystemManager &EcsManager::getSystemManager()
    {
        return _systemManager;
    }

    ResourceManager &EcsManager::getResourceManager() {
        return _resourceManager;
    }
}