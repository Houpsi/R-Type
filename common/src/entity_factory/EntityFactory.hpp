/*
** EPITECH PROJECT, 2026
** R_Type
** File description:
** EntityFactory
*/

#ifndef R_TYPE_ENTITYFACTORY_HPP
#define R_TYPE_ENTITYFACTORY_HPP

#include "EcsManager.hpp"
#include "Entity.hpp"
#include "enums/EntityType.hpp"
#include <memory>

namespace cmn {

    class EntityFactory {
    public:
        enum class Context {
            SERVER,
            CLIENT
        };

        static std::shared_ptr<ecs::Entity> createEntity(
            ecs::EcsManager &registry,
            EntityType type,
            float x,
            float y,
            Context context,
            int hp = 0, int id = -1
        );

    private:
        static void _initPlayer(ecs::EcsManager &ecs, std::shared_ptr<ecs::Entity> entity, Context context);
        static void _initEnemy(ecs::EcsManager &ecs, std::shared_ptr<ecs::Entity> entity, Context context, EntityType type);
        static void _initProjectile(ecs::EcsManager& ecs, std::shared_ptr<ecs::Entity> entity, Context context);
        static void _initBoss(ecs::EcsManager &ecs, std::shared_ptr<ecs::Entity> entity, Context context, int hp);
        static void _initBackground(ecs::EcsManager &ecs, std::shared_ptr<ecs::Entity> entity, Context context, EntityType type);
    };

}

#endif// R_TYPE_ENTITYFACTORY_HPP
