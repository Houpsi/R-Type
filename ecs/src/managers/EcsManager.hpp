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
        Entity createEntity(std::size_t id);
        void deleteEntity(Entity entity);
        void destroyEntities(std::vector<ecs::Entity> &entitiesToDestroy);
        void updateSystems();
        void initComponents();


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
        std::vector<Entity> getEntitiesWithComponent()
        {
            std::vector<Entity> result;
            auto bit = _componentManager.getComponentBitId<T>();

            for (Entity entity = 0; entity < cmn::MAX_ENTITIES; ++entity) {
                Signature sig = _entityManager.getSignature(entity);
                if (sig.test(bit)) {
                    result.push_back(entity);
                }
            }
            return result;
        }

        template <typename T>
        void addSystem()
        {
            return _systemManager.addSystem<T>(*this);
        }

        template <typename T, typename... Args>
        void addSystem(Args&&... args) {
            return _systemManager.addSystem<T>(*this, std::forward<Args>(args)...);
        }

        template <typename... Args>
        bool entityHasComponent(Entity entity)
        {
            Signature entitySignature = _entityManager.getSignature(entity);
            Signature targetSignature;
            (targetSignature.set(_componentManager.getComponentBitId<Args>()), ...);
            return (entitySignature & targetSignature) == targetSignature;

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