/*
** EPITECH PROJECT, 2025
** R_Type
** File description:
** DataTranslator
*/

#include "DataTranslator.hpp"
#include "constants/GameConstants.hpp"
#include "components/Animation.hpp"
#include "components/Collision.hpp"
#include "components/Destroy.hpp"
#include "components/Enemy.hpp"
#include "components/InputPlayer.hpp"
#include "components/PlayerAnimation.hpp"
#include "components/Position.hpp"
#include "components/Sound.hpp"
#include "components/Sprite.hpp"
#include "constants/GameConstants.hpp"
#include "entity_factory/EntityFactory.hpp"
#include "enums/EntityType.hpp"
#include "enums/Key.hpp"
#include <list>

namespace cmn {

    using InputFn = void (*)(Keys, const std::shared_ptr<ecs::InputPlayer>&);

    constexpr std::array<InputFn, 6> functionArray = {{
        [](Keys key, const std::shared_ptr<ecs::InputPlayer>&component) {
            component->setDown(key == Keys::Down);
        },
        [](Keys key, const std::shared_ptr<ecs::InputPlayer>&component) {
            component->setUp(key == Keys::Up);
        },
        [](Keys key, const std::shared_ptr<ecs::InputPlayer>& component) {
            component->setLeft(key == Keys::Left);
        },
        [](Keys key, const std::shared_ptr<ecs::InputPlayer>& component) {
            component->setRight(key == Keys::Right);
        },
        [](Keys key, const std::shared_ptr<ecs::InputPlayer>& component) {
            component->setSpacebar(key == Keys::Space);
        },
        [](Keys key, const std::shared_ptr<ecs::InputPlayer>& component) {
            component->setR(key == Keys::R);
        }
    }};

    void DataTranslator::_injectInput(ecs::EcsManager &ecs, inputData &input, std::unordered_map<int, uint64_t> playerIdEntityMap)
    {
        uint32_t playerId = input.playerId;
        uint64_t const entityId = playerIdEntityMap[static_cast<int>(playerId)];

        for (auto &entity : ecs.getEntitiesWithComponent<ecs::InputPlayer>()) {
            if (entity->getId() == entityId) {
                auto component = entity->getComponent<ecs::InputPlayer>();
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
            if (entity->getId() == position.entityId) {
                auto component = entity->getComponent<ecs::Position>();
                component->setX(position.posX);
                component->setY(position.posY);
                break;
            }
        }
    }

    void DataTranslator::_injectNewEntity(ecs::EcsManager &ecs, newEntityData &newEntity)
    {
        auto entity =  cmn::EntityFactory::createEntity(ecs,
                        static_cast<EntityType>(newEntity.type),
                        newEntity.posX, newEntity.posY,
                        cmn::EntityFactory::Context::CLIENT, 0, newEntity.entityId);

    }

    void DataTranslator::_deleteEntity(ecs::EcsManager &ecs, deleteEntityData &deleteEntity)
    {
        for (auto &entity : ecs.getEntitiesWithComponent<ecs::Position>()) {
            if (entity->getId() == deleteEntity.entityId) {
                entity->addComponent<ecs::Destroy>();
                break;
            }
        }
    }

    void DataTranslator::_soundEntity(ecs::EcsManager &ecs, soundData &sound)
    {
        for (auto &entity : ecs.getEntities()) {
            if (entity->getId() == idEntityForMusic) {
                entity->addComponent<ecs::Sound>(static_cast<int>(sound.soundId), false);
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
                }  else if constexpr (std::is_same_v<T, soundData>) {
                    soundData &sound = arg;
                    _soundEntity(ecs, sound);
                }
            }, data);
    }

}// namespace cmn