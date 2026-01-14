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
#include "components/ComponentTypes.hpp"
#include "components/animation/Animation.hpp"
#include "components/background/Background.hpp"
#include "components/destroy/Destroy.hpp"
#include "components/enemy/Enemy.hpp"
#include "components/inputPlayer/InputPlayer.hpp"
#include "components/playerAnimation/PlayerAnimation.hpp"
#include "components/sound/Sound.hpp"
#include "components/sprite/Sprite.hpp"
#include "components/velocity/Velocity.hpp"
#include "components/position/Position.hpp"

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

    Entity EcsManager::createEntity(std::size_t id)
    {
        return _entityManager.createEntity(id);
    }

    void EcsManager::deleteEntity(Entity entity)
    {
        _componentManager.entityDestroyed(entity);
        _entityManager.deleteEntity(entity);
    }

    void EcsManager::updateSystems() {
        _systemManager.updateSystems(*this);
    }

    void EcsManager::initComponents()
    {
        _componentManager.registerComponentType<ecs::Animation>();
        _componentManager.registerComponentType<ecs::Background>();
        _componentManager.registerComponentType<ecs::Collision>();
        _componentManager.registerComponentType<ecs::Destroy>();
        _componentManager.registerComponentType<ecs::Enemy>();
        _componentManager.registerComponentType<ecs::Health>();
        _componentManager.registerComponentType<ecs::InputPlayer>();
        _componentManager.registerComponentType<ecs::PlayerAnimation>();
        _componentManager.registerComponentType<ecs::Shoot>();
        _componentManager.registerComponentType<ecs::Sound>();
        _componentManager.registerComponentType<ecs::Sprite>();
        _componentManager.registerComponentType<ecs::Velocity>();
        _componentManager.registerComponentType<ecs::Position>();
    }

}