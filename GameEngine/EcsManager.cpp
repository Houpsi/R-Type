//
// Created by aleks on 27/11/2025.
//

#include "EcsManager.hpp"

std::shared_ptr<Entity> EcsManager::createEntity() {
    auto entity = std::make_shared<Entity>();
    _entities.push_back(entity);
    return entity;
}




void EcsManager::updateSystems() {
    for (const auto& system : _systems) {
        system->update(*this);
    }
}