/*
** EPITECH PROJECT, 2026
** R_Type
** File description:
** EntityFactory
*/


#include "EntityFactory.hpp"

#include "components/Animation.hpp"
#include "components/Background.hpp"
#include "components/Collision.hpp"
#include "components/Enemy.hpp"
#include "components/InputPlayer.hpp"
#include "components/PlayerAnimation.hpp"
#include "components/Position.hpp"
#include "components/Sound.hpp"
#include "components/Sprite.hpp"
#include "components/Velocity.hpp"
#include "constants/GameConstants.hpp"

namespace cmn {

    std::shared_ptr<ecs::Entity> EntityFactory::createEntity(
        ecs::EcsManager &ecs,
        EntityType type,
        float x,
        float y,
        Context context, uint32_t hp, int id)
    {
        std::shared_ptr<ecs::Entity> entity;
        if (id != -1)
            entity = ecs.createEntity(id);
        else
            entity = ecs.createEntity();
        entity->addComponent<ecs::Position>(x, y);
        switch (type) {
            case EntityType::Player:
                _initPlayer(ecs, entity, context);
                break;
            case EntityType::Crochet:
            case EntityType::Plane:
                _initEnemy(ecs, entity, context, type);
                break;
            case cmn::EntityType::PlayerProjectile:
                _initProjectile(ecs, entity, context);
                break;
            case cmn::EntityType::Boss1:
                _initBoss(ecs, entity, context, hp);
                break;
            case cmn::EntityType::BackgroundPlanets:
            case cmn::EntityType::BackgroundStars:
                _initBackground(ecs, entity, context, type);
            break;
            default:
                break;
        }
        return entity;
    }

    void EntityFactory::_initPlayer(ecs::EcsManager& ecs, std::shared_ptr<ecs::Entity> entity, Context context) {
        if (context == Context::CLIENT) {
            entity->addComponent<ecs::Sprite>(ecs.getResourceManager().getTexture(std::string(playerSpriteSheet)), playerSpriteScale);
            entity->addComponent<ecs::PlayerAnimation>();
            entity->addComponent<ecs::InputPlayer>();
        } else {
            entity->addComponent<ecs::Health>(playerHealth);
            entity->addComponent<ecs::Position>(playerPosX, playerPosY);
            entity->addComponent<ecs::InputPlayer>();
            entity->addComponent<ecs::Collision>(ecs::TypeCollision::PLAYER, cmn::playerWidth, cmn::playerHeight);
            entity->addComponent<ecs::Shoot>(cmn::playerDamage, cmn::playerCoolDown);
        }
    }

    void EntityFactory::_initEnemy(ecs::EcsManager& ecs, std::shared_ptr<ecs::Entity> entity, Context context, EntityType type) {
        if (context == Context::CLIENT) {
            if (type == EntityType::Plane) {
                 entity->addComponent<ecs::Sprite>(ecs.getResourceManager().getTexture(std::string(monsterSpriteSheet)), monsterSpriteScale);
                 entity->addComponent<ecs::Animation>(cmn::monsterAnimationSize, cmn::monsterAnimationOffset, monsterAnimationNumberFrame);
            } else if (type == EntityType::Crochet) {
                 entity->addComponent<ecs::Sprite>(ecs.getResourceManager().getTexture(std::string(monster2SpriteSheet)), monster2SpriteScale);
                 entity->addComponent<ecs::Animation>(cmn::monster2AnimationSize, monster2AnimationOffset, monster2AnimationNumberFrame);
            }
        } else {
            entity->addComponent<ecs::Health>(monsterHealth);
            entity->addComponent<ecs::Enemy>();
            entity->addComponent<ecs::Collision>(
                ecs::TypeCollision::ENEMY,
                monsterCollisionWidth,
                monsterCollisionHeight
            );
        }
    }

    void EntityFactory::_initProjectile(ecs::EcsManager &ecs,std::shared_ptr<ecs::Entity> entity, Context context) {
        entity->addComponent<ecs::Velocity>(cmn::playerProjectileSpeed, cmn::playerProjectileDirection);

        if (context == Context::CLIENT) {
            entity->addComponent<ecs::Sprite>(ecs.getResourceManager().getTexture(std::string(cmn::playerProjectileSpriteSheet)), cmn::playerProjectileScale);
            entity->addComponent<ecs::Animation>(cmn::playerProjectileAnimationSize, cmn::playerProjectileAnimationOffset, cmn::playerProjectileAnimationNumberFrame);
            entity->addComponent<ecs::Sound>(1, false);
        } else {
            entity->addComponent<ecs::Shoot>(cmn::playerDamage, 0);
            entity->addComponent<ecs::Collision>(
                ecs::TypeCollision::PLAYER_PROJECTILE,
                cmn::playerProjectileCollisionWidth,
                cmn::playerProjectileCollisionHeight
            );
        }
    }

    void EntityFactory::_initBoss(ecs::EcsManager &ecs, std::shared_ptr<ecs::Entity> entity, Context context, int hp) {
        if (context == Context::CLIENT) {
            entity->addComponent<ecs::Sprite>(ecs.getResourceManager().getTexture(std::string(cmn::boss1SpriteSheet)), cmn::boss1SpriteScale);
            entity->addComponent<ecs::Animation>(cmn::boss1AnimationSize, cmn::boss1AnimationOffset, cmn::boss1AnimationNumberFrame);
        } else {
            entity->addComponent<ecs::Health>(hp);
            entity->addComponent<ecs::Collision>(
                ecs::TypeCollision::ENEMY,
                cmn::boss1CollisionWidth,
                cmn::boss1CollisionHeight
            );
        }
    }

    void EntityFactory::_initBackground(ecs::EcsManager &ecs, std::shared_ptr<ecs::Entity> entity, Context context, EntityType type) {

        float velX = 0;
        float velY = 0;
        std::string texturePath;
        int bgSize = 0;

        if (type == EntityType::BackgroundStars) {
            velX = veloStars.x;
            velY = veloStars.y;
            texturePath = static_cast<std::string>(pathBackgroundStars);
            bgSize = sizeStars;
        } else {
            velX = veloPlanets.x;
            velY = veloPlanets.y;
            texturePath = static_cast<std::string>(pathBackgroundPlanets);
            bgSize = sizePlanets;
        }
        entity->addComponent<ecs::Velocity>(velX, velY);
        entity->addComponent<ecs::Background>(bgSize);

        if (context == Context::CLIENT) {
            entity->addComponent<ecs::Sprite>(
                ecs.getResourceManager().getTexture(std::string(texturePath)),
                backgroundSpriteScale
            );
        }
    }
}