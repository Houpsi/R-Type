/*
** EPITECH PROJECT, 2025
** r-type_client
** File description:
** EcsManager
*/

#include "EcsManager.hpp"

namespace ECS {
std::shared_ptr<Entity> EcsManager::createEntity() {
    auto entity = std::make_shared<Entity>();
    _entities.push_back(entity);
    return entity;
}

std::vector<std::shared_ptr<Entity>> EcsManager::getEntities() {
    return _entities;
}

void EcsManager::setDeltaTime(float dt)
{
    _deltaTime = dt;
}
float EcsManager::deltaTime() const
{
    return _deltaTime;
}

void EcsManager::updateSystems() {
    for (const auto& system : _systems) {
        system->update(*this);
    }
}
}