/*
** EPITECH PROJECT, 2026
** R_Type
** File description:
** ShootManager
*/


#ifndef R_TYPE_SHOOTMANAGER_HPP
#define R_TYPE_SHOOTMANAGER_HPP


#include <unordered_map>
#include <functional>
#include <memory>
#include "components/Shoot.hpp"
#include "Entity.hpp"
#include "shared_data/SharedData.hpp"
#include "EcsManager.hpp"

namespace server {
    class ShootManager {
    public:
        ShootManager();
        void shoot(ecs::EcsManager &ecsManager, std::shared_ptr<cmn::SharedData> &sharedData, const std::shared_ptr<ecs::Entity> &entity);
    private:
        void _normalShoot(ecs::EcsManager &ecsManager, std::shared_ptr<cmn::SharedData> &sharedData, const std::shared_ptr<ecs::Entity> &shoot);
        std::unordered_map<ecs::Shoot::ShootingType, std::function<void(ecs::EcsManager &ecsManager, std::shared_ptr<cmn::SharedData> &sharedData, const std::shared_ptr<ecs::Entity> &entity)>> _shootMethods;
    };
}


#endif //R_TYPE_SHOOTMANAGER_HPP
