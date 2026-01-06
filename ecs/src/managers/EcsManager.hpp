/*
** EPITECH PROJECT, 2025
** R_Type
** File description:
** EcsManager
*/

#ifndef ECSMANAGER_HPP
    #define ECSMANAGER_HPP
#include "Entity.hpp"
#include "ResourceManager.hpp"
#include "systems/System.hpp"
#include "EntityManager.hpp"
#include "ComponentManager.hpp"
#include "SystemManager.hpp"
#include <memory>
#include <vector>

namespace ecs {
    class EcsManager {
    public:
        EntityManager &getEntityManager();
        ComponentManager &getComponentManager();
        SystemManager &getSystemManager();
        ResourceManager &getResourceManager();
    private:
        EntityManager _entityManager;
        ComponentManager _componentManager;
        SystemManager _systemManager;
        ResourceManager _resourceManager;
    };
}

#endif //ECSMANAGER_HPP