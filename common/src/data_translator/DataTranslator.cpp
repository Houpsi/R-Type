/*
** EPITECH PROJECT, 2025
** R_Type
** File description:
** DataTranslator
*/

#include "DataTranslator.hpp"
#include "constants/GameConstants.hpp"
#include "components/animation/Animation.hpp"
#include "components/inputPlayer/InputPlayer.hpp"
#include "components/playerAnimation/PlayerAnimation.hpp"
#include "components/position/Position.hpp"
#include "components/sound/Sound.hpp"
#include "components/sprite/Sprite.hpp"
#include "components/destroy/Destroy.hpp"
#include "enums/EntityType.hpp"
#include "enums/Key.hpp"
#include "components/ComponentTypes.hpp"
#include <list>

namespace cmn {

    using InputFn = void (*)(Keys, ecs::InputPlayer&);

    constexpr std::array<InputFn, 6> functionArray = {{
        [](Keys key, ecs::InputPlayer&component) {
            component.setDown(key == Keys::Down);
        },
        [](Keys key, ecs::InputPlayer&component) {
            component.setUp(key == Keys::Up);
        },
        [](Keys key, ecs::InputPlayer& component) {
            component.setLeft(key == Keys::Left);
        },
        [](Keys key, ecs::InputPlayer& component) {
            component.setRight(key == Keys::Right);
        },
        [](Keys key, ecs::InputPlayer& component) {
            component.setSpacebar(key == Keys::Space);
        },
        [](Keys key, ecs::InputPlayer& component) {
            component.setR(key == Keys::R);
        }
    }};

    void DataTranslator::_injectInput(ecs::EcsManager &ecs, inputData &input, std::unordered_map<int, uint64_t> playerIdEntityMap)
    {
        uint32_t playerId = input.playerId;
        uint64_t const entityId = playerIdEntityMap[static_cast<int>(playerId)];

        for (auto entity : ecs.getEntitiesWithComponent<ecs::InputPlayer>()) {
            if (entity == entityId) {
                // auto component = entity->getComponent<ecs::InputPlayer>();
                auto component = ecs.getComponent<ecs::InputPlayer>(entity);
                Keys const key = static_cast<Keys>(input.key);
                for (const auto &function : functionArray) {
                    function(key, component);
                }
                break;
            }
        }
    }

    void DataTranslator::_injectPosition(ecs::EcsManager &ecs, positionData &position)
    {
        for (auto &entity : ecs.getEntitiesWithComponent<ecs::Position>()) {
            if (entity == position.entityId) {
                // auto component = entity->getComponent<ecs::Position>();
                auto component = ecs.getComponent<ecs::Position>(entity);
                component.setX(position.posX);
                component.setY(position.posY);
                break;
            }
        }
    }

    void DataTranslator::_injectNewEntity(ecs::EcsManager &ecs, newEntityData &newEntity)
    {
        // auto entity = ecs.createEntity(newEntity.entityId);
        auto entity = ecs.createEntity();

        ecs.addComponentToEntity(entity, ecs::Position(newEntity.posX, newEntity.posY));
        // entity->addComponent<ecs::Position>(newEntity.posX, newEntity.posY);
        if (static_cast<EntityType>(newEntity.type) == EntityType::Player) {
            ecs.addComponentToEntity(entity, ecs::Sprite(ecs.getResourceManager().getTexture(std::string(playerSpriteSheet)), playerSpriteScale));
            ecs.addComponentToEntity(entity, ecs::PlayerAnimation());
            ecs.addComponentToEntity(entity, ecs::Sound(std::string(playerShootSound)));
            ecs.addComponentToEntity(entity, ecs::InputPlayer());
            // entity->addComponent<ecs::Sprite>(ecs.getResourceManager().getTexture(std::string(playerSpriteSheet)), playerSpriteScale);
            // entity->addComponent<ecs::PlayerAnimation>();
            // entity->addComponent<ecs::Sound>(std::string(playerShootSound));
            // entity->addComponent<ecs::InputPlayer>();
        }
        if (static_cast<EntityType>(newEntity.type) == EntityType::Monster) {
            ecs.addComponentToEntity(entity, ecs::Sprite(ecs.getResourceManager().getTexture(std::string(monsterSpriteSheet)), monsterSpriteScale));
            ecs.addComponentToEntity(entity, ecs::Animation(monsterAnimationSize, monsterAnimationOffset, monsterAnimationNumberFrame));
            // entity->addComponent<ecs::Sprite>(ecs.getResourceManager().getTexture(std::string(monsterSpriteSheet)), monsterSpriteScale);
            // entity->addComponent<ecs::Animation>(monsterAnimationSize, monsterAnimationOffset, monsterAnimationNumberFrame);
        }
        if (static_cast<EntityType>(newEntity.type) == EntityType::PlayerProjectile) {
            ecs.addComponentToEntity(entity, ecs::Sprite(ecs.getResourceManager().getTexture(std::string(playerProjectileSpriteSheet)), playerProjectileScale));
            ecs.addComponentToEntity(entity, ecs::Animation(playerProjectileAnimationSize, playerProjectileAnimationOffset, playerProjectileAnimationNumberFrame));
            // entity->addComponent<ecs::Sprite>(ecs.getResourceManager().getTexture(std::string(playerProjectileSpriteSheet)), playerProjectileScale);
            // entity->addComponent<ecs::Animation>(playerProjectileAnimationSize, playerProjectileAnimationOffset, playerProjectileAnimationNumberFrame);
        }
    }

    void DataTranslator::_deleteEntity(ecs::EcsManager &ecs, deleteEntityData &deleteEntity)
    {
        for (auto &entity : ecs.getEntitiesWithComponent<ecs::Position>()) {
            if (entity == deleteEntity.entityId) {
                ecs.addComponentToEntity(entity, ecs::types::Destroy());
                break;
            }
        }
    }

    void DataTranslator::translate(ecs::EcsManager &ecs, packetData &data, const std::unordered_map<int, uint64_t>& playerIdEntityMap)
    {
        std::visit([&ecs, playerIdEntityMap](auto &&arg)
            {
                using T = std::decay_t<decltype(arg)>;
                if constexpr (std::is_same_v<T, inputData>) {
                    inputData &input = arg;
                    _injectInput(ecs, input, playerIdEntityMap);
                } else if constexpr (std::is_same_v<T, positionData>) {
                    positionData &position = arg;
                    _injectPosition(ecs, position);
                } else if constexpr (std::is_same_v<T, newEntityData>) {
                    newEntityData &newEntity = arg;
                    _injectNewEntity(ecs, newEntity);
                } else if constexpr (std::is_same_v<T, deleteEntityData>) {
                    deleteEntityData &deleteEntity = arg;
                    _deleteEntity(ecs, deleteEntity);
                }
            }, data);
    }

}// namespace cmn