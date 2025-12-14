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
#include <memory>
#include <vector>

namespace ecs {
class EcsManager {
  public:
    EcsManager() = default;
    ~EcsManager() = default;
    std::shared_ptr<Entity> createEntity();
    std::shared_ptr<Entity> createEntity(std::size_t id);
    std::vector<std::shared_ptr<Entity>> &getEntities();
    void updateSystems();
    void setDeltaTime(float dt);
    float getDeltaTime() const;
    ResourceManager &getResourceManager();
    [[nodiscard]] std::shared_ptr<Entity> getEntityById(uint64_t id) const;

    template <typename T, typename... Args>
    std::shared_ptr<T> addSystem(Args&&... args) {
        auto system = std::make_shared<T>(std::forward<Args>(args)...);
        _systems.push_back(system);
        return system;
    }

    template <typename T>
    std::shared_ptr<T> addSystem() {
        auto system = std::make_shared<T>();
        _systems.push_back(system);
        return system;
    }

    template <typename T>
    std::vector<std::shared_ptr<Entity>> getEntitiesWithComponent() const {
        std::vector<std::shared_ptr<Entity>> result;
        for (const auto& entity : _entities) {
            if (entity->getComponent<T>()) {
                result.push_back(entity);
            }
        }
        return result;
    }
  private:
    float _deltaTime = 0.0f;
    std::vector<std::shared_ptr<System>> _systems;
    std::vector<std::shared_ptr<Entity>> _entities;

    ResourceManager _resourceManager;
    size_t _nextEntityId = 5;
};
}

#endif //ECSMANAGER_HPP