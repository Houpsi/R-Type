//
// Created by aleks on 27/11/2025.
//

#ifndef BOOTSTRAP_ECSMANAGER_HPP
#define BOOTSTRAP_ECSMANAGER_HPP
#include <memory>
#include <vector>

#include "Entity.hpp"
#include "Systems/System.hpp"


class EcsManager {
    public:
        EcsManager() = default;
        ~EcsManager() = default;
        std::shared_ptr<Entity> createEntity();
        void DestroyEntity(std::string name);

     std::vector<std::shared_ptr<Entity>> getEntities() {
         return _entities;
     }

        template <typename T, typename... Args>
        std::shared_ptr<T> addSystem(Args&&... args) {
                auto system = std::make_shared<T>(std::forward<Args>(args)...);
                _systems.push_back(system);
                return system;
            }

        void updateSystems();

    template <typename T>
[[nodiscard]] std::vector<std::shared_ptr<Entity>> getEntitiesWithComponent() const {
        std::vector<std::shared_ptr<Entity>> result;
        for (const auto& entity : _entities) {
            if (entity->getComponent<T>()) {
                result.push_back(entity);
            }
        }
        return result;
    }

    private:
        std::vector<std::shared_ptr<System>> _systems;
        std::vector<std::shared_ptr<Entity>> _entities;
};


#endif //BOOTSTRAP_ECSMANAGER_HPP