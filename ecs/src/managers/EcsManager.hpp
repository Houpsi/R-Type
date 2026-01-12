/*
** EPITECH PROJECT, 2025
** R_Type
** File description:
** EcsManager
*/

#ifndef ECSMANAGER_HPP
    #define ECSMANAGER_HPP
#include "ResourceManager.hpp"
#include "systems/system/ISystem.hpp"
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
        float getDeltaTime() const;
        void setDeltaTime(float dt);
    private:
        EntityManager _entityManager;
        ComponentManager _componentManager;
        SystemManager _systemManager;
        ResourceManager _resourceManager;
        float _deltaTime = 0.0f;

    };
}

#endif //ECSMANAGER_HPP