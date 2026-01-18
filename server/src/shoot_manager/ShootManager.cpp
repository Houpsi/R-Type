/*
** EPITECH PROJECT, 2026
** R_Type
** File description:
** ShootManager
*/


#include "ShootManager.hpp"
#include "components/Position.hpp"
#include "components/Collision.hpp"
#include "entity_factory/EntityFactory.hpp"
#include "packet_data/NewEntityData.hpp"
#include "EcsConstant.hpp"
#include "constants/GameConstants.hpp"
#include <vector>

namespace server {
    ShootManager::ShootManager()
    {
        _shootMethods[ecs::Shoot::ShootingType::Normal] = [this](ecs::EcsManager &ecsManager, std::shared_ptr<ServerSharedData> &sharedData, const std::shared_ptr<ecs::Entity> &shoot) { _normalShoot(ecsManager, sharedData, shoot); };
        _shootMethods[ecs::Shoot::ShootingType::Shotgun] = [this](ecs::EcsManager &ecsManager, std::shared_ptr<ServerSharedData> &sharedData, const std::shared_ptr<ecs::Entity> &shoot) { _shotgun(ecsManager, sharedData, shoot); };
        _shootMethods[ecs::Shoot::ShootingType::Gatling] = [this](ecs::EcsManager &ecsManager, std::shared_ptr<ServerSharedData> &sharedData, const std::shared_ptr<ecs::Entity> &shoot) { _gatling(ecsManager, sharedData, shoot); };
    }

    void ShootManager::shoot(ecs::EcsManager &ecsManager, std::shared_ptr<ServerSharedData> &sharedData, const std::shared_ptr<ecs::Entity> &entity, int lobbyId)
    {
        const auto &shootComp = entity->getComponent<ecs::Shoot>();

        if (shootComp) {
            auto shootingType = shootComp->getActiveShootingType();
            _shootMethods[shootingType](ecsManager, sharedData, entity);
        }
        _gameLobbyId = lobbyId;
    }

    void ShootManager::_normalShoot(ecs::EcsManager &ecsManager, std::shared_ptr<ServerSharedData> &sharedData, const std::shared_ptr<ecs::Entity> &entity)
    {
        const auto &shoot = entity->getComponent<ecs::Shoot>();
        if (shoot->getTimeSinceLastShot() >= shoot->getCooldown()) {
            auto positionCpn = entity->getComponent<ecs::Position>();
            auto collisionCpn = entity->getComponent<ecs::Collision>();

            shoot->setTimeSinceLastShot(0);

            float const posX = positionCpn->getX() + collisionCpn->getHeight();
            float const posY = entity->getComponent<ecs::Position>()->getY();

            auto newProjectile = cmn::EntityFactory::createEntity(
                    ecsManager,
                    cmn::EntityType::PlayerProjectile,
                    posX,
                    posY,
                    cmn::EntityFactory::Context::SERVER,
                    0,
                    -1,
                    {ecs::dir::right, ecs::dir::neutral});

            cmn::newEntityData data = {newProjectile->getId(), cmn::EntityType::PlayerProjectile, posX, posY};
            sharedData->addLobbyUdpPacketToSend(_gameLobbyId, data);
        }
    }

    void ShootManager::_shotgun(ecs::EcsManager &ecsManager, std::shared_ptr<ServerSharedData> &sharedData, const std::shared_ptr<ecs::Entity> &entity)
    {
        const auto &shoot = entity->getComponent<ecs::Shoot>();
        if (shoot->getTimeSinceLastShot() >= cmn::shotgunCooldown) {
            shoot->setTimeSinceLastShot(0);
            shoot->updateShootingType();

            auto positionCpn = entity->getComponent<ecs::Position>();
            auto collisionCpn = entity->getComponent<ecs::Collision>();

            float const posX = positionCpn->getX() + collisionCpn->getHeight();
            float const posY = entity->getComponent<ecs::Position>()->getY();
            std::vector<float> yDirections = {ecs::dir::normalized45degreesUp, ecs::dir::normalized23degreesUp, ecs::dir::neutral, ecs::dir::normalized23degreesDown, ecs::dir::normalized45degreesDown};
            for (auto yDirection : yDirections) {
                auto newProjectile = cmn::EntityFactory::createEntity(
                        ecsManager,
                        cmn::EntityType::PlayerProjectile,
                        posX,
                        posY,
                        cmn::EntityFactory::Context::SERVER,
                        0,
                        -1,
                        {ecs::dir::right, yDirection}
                );
                cmn::newEntityData newProjectileData = {newProjectile->getId(), cmn::EntityType::PlayerProjectile, posX, posY};
                sharedData->addLobbyUdpPacketToSend(_gameLobbyId, newProjectileData);
            }
        }
    }

    void ShootManager::_gatling(ecs::EcsManager &ecsManager, std::shared_ptr<ServerSharedData> &sharedData, const std::shared_ptr<ecs::Entity> &entity)
    {
        const auto &shoot = entity->getComponent<ecs::Shoot>();
        if (shoot->getTimeSinceLastShot() >= cmn::gatlingCooldown) {
            shoot->setTimeSinceLastShot(0);
            shoot->updateShootingType();
            auto positionCpn = entity->getComponent<ecs::Position>();
            auto collisionCpn = entity->getComponent<ecs::Collision>();

            float const posX = positionCpn->getX() + collisionCpn->getHeight();
            float const posY = entity->getComponent<ecs::Position>()->getY();

            auto newProjectile = cmn::EntityFactory::createEntity(
                    ecsManager,
                    cmn::EntityType::PlayerProjectile,
                    posX,
                    posY,
                    cmn::EntityFactory::Context::SERVER,
                    0,
                    -1,
                    {ecs::dir::right, ecs::dir::neutral}
            );

            cmn::newEntityData data = {newProjectile->getId(), cmn::EntityType::PlayerProjectile, posX, posY};
            sharedData->addLobbyUdpPacketToSend(_gameLobbyId, data);
        }
    }
}