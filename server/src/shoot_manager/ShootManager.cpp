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

namespace server {
    ShootManager::ShootManager()
    {
        _shootMethods[ecs::Shoot::ShootingType::Normal] = [this](ecs::EcsManager &ecsManager, std::shared_ptr<cmn::SharedData> &sharedData, const std::shared_ptr<ecs::Entity> &shoot) { _normalShoot(ecsManager, sharedData, shoot); };
    }

    void ShootManager::shoot(ecs::EcsManager &ecsManager, std::shared_ptr<cmn::SharedData> &sharedData, const std::shared_ptr<ecs::Entity> &entity)
    {
        const auto &shootComp = entity->getComponent<ecs::Shoot>();
        for (auto const &shootingType : shootComp->getActiveShootingTypes()) {
            _shootMethods[shootingType](ecsManager, sharedData, entity);
        }
    }

    void ShootManager::_normalShoot(ecs::EcsManager &ecsManager, std::shared_ptr<cmn::SharedData> &sharedData, const std::shared_ptr<ecs::Entity> &entity)
    {
        const auto &shoot = entity->getComponent<ecs::Shoot>();
        if (shoot->getTimeSinceLastShot() >= shoot->getCooldown()) {
            auto positionCpn = entity->getComponent<ecs::Position>();
            auto collisionCpn = entity->getComponent<ecs::Collision>();

            shoot->setTimeSinceLastShot(0);

            float const posX = positionCpn->getX() + collisionCpn->getHeight();
            float const posY = entity->getComponent<ecs::Position>()->getY();

            auto projectile = cmn::EntityFactory::createEntity(ecsManager,
                                                               cmn::EntityType::PlayerProjectile,
                                                               posX,
                                                               posY,
                                                               cmn::EntityFactory::Context::SERVER);

            cmn::newEntityData data = {projectile->getId(), cmn::EntityType::PlayerProjectile, posX, posY};
            sharedData->addUdpPacketToSend(data);
        }
    }
}