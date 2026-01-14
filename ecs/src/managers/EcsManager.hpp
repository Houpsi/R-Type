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
    class SystemManager;

    class EcsManager {
    public:
        Entity createEntity();
        void deleteEntity(Entity entity);
        void destroyEntities(std::vector<ecs::Entity> &entitiesToDestroy);

        template <typename T>
        void registerComponent()
        {
            _componentManager.registerComponentType<T>();
        }

        template <typename T>
        void addComponentToEntity(Entity entity, T comp)
        {
            _componentManager.addComponent<T>(entity, comp);

            auto entitySignature = _entityManager.getSignature(entity);
            auto bitIndex = _componentManager.getComponentBitId<T>();
            entitySignature.set(bitIndex, true);
            _entityManager.setSignature(entity, entitySignature);
            _systemManager.onSignatureChanged(entity, entitySignature);
        }

        template <typename T>
        void removeComponentFromEntity(Entity entity, T comp)
        {
            _componentManager.removeComponent<T>(entity, comp);

            auto entitySignature = _entityManager.getSignature(entity);
            auto bitIndex = _componentManager.getComponentBitId<T>();
            entitySignature.set(bitIndex, false);
            _entityManager.setSignature(entity, entitySignature);
            _systemManager.onSignatureChanged(entity, entitySignature);
        }

        template <typename T>
        T& getComponent(Entity entity)
        {
            return _componentManager.getComponent<T>(entity);
        }

        template <typename T>
        uint8_t getComponentType()
        {
            return _componentManager.getComponentBitId<T>();
        }

        template <typename T>
        std::vector<std::shared_ptr<Entity>> getEntitiesWithComponent()
        {
            auto entities =  _entityManager.getAvailableEntities();
            std::vector<std::shared_ptr<Entity>> result;

            for (int i = 0; i <entities.size(); i++) {
                if (_componentManager.getComponent<T>(entities.emplace(i))) {
                    entities.emplace(i);
                }
            }
            return result;
        }

        template <typename T>
        std::shared_ptr<T> addSystem()
        {
            return _systemManager.addSystem<T>(*this);
        }

        ResourceManager& getResourceManager();
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