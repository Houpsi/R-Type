/*
** EPITECH PROJECT, 2025
** R_Type
** File description:
** DataTranslator
*/

#include "DataTranslator.hpp"
#include "components/InputPlayer.hpp"
#include "components/Position.hpp"
#include "enums/Key.hpp"
#include <functional>
#include <list>
#include <unordered_map>

namespace cmn {

    const std::list<std::function<void(Keys, std::shared_ptr<ecs::InputPlayer>)>> functionList = {
        [](Keys key,std::shared_ptr<ecs::InputPlayer> component) {key == Keys::Down ? component->setDown(true) : component->setDown(false);},
        [](Keys key,std::shared_ptr<ecs::InputPlayer> component) {key == Keys::Up ? component->setUp(true) : component->setUp(false);},
        [](Keys key,std::shared_ptr<ecs::InputPlayer> component) {key == Keys::Left ? component->setLeft(true) : component->setLeft(false);},
        [](Keys key,std::shared_ptr<ecs::InputPlayer> component) {key == Keys::Right ? component->setRight(true) : component->setRight(false);},
        [](Keys key,std::shared_ptr<ecs::InputPlayer> component) {key == Keys::Space ? component->setSpacebar(true) : component->setSpacebar(false);},
        [](Keys key,std::shared_ptr<ecs::InputPlayer> component) {key == Keys::R ? component->setR(true) : component->setR(false);},

    };

    void DataTranslator::_injectInput(ecs::EcsManager &ecs, inputPacket &input, int id)
    {
        for (auto &entity : ecs.getEntitiesWithComponent<ecs::InputPlayer>()) {
            if (entity->_id == id) {
                auto component = entity->getComponent<ecs::InputPlayer>();
                Keys key = static_cast<Keys>(input.key);
                for (auto &function : functionList) {
                    function(key, component);
                }
            }
        }
    }

    void DataTranslator::_injectPosition(ecs::EcsManager &ecs, positionPacket &position, int id)
    {
        for (auto &entity : ecs.getEntitiesWithComponent<ecs::Position>()) {
            if (entity->_id == id) {

            }
        }
    }

    void DataTranslator::translate(ecs::EcsManager &ecs, packetData &data)
    {
        std::visit([data, this, &ecs](auto &&arg)
            {
                using T = std::decay_t<decltype(arg)>;
                if constexpr (std::is_same_v<T, inputPacket>) {
                    inputPacket &input = arg;
                    _injectInput(ecs, input, data.entityId);
                } else if constexpr (std::is_same_v<T, positionPacket>) {
                    const positionPacket &position = arg;
                } else if constexpr (std::is_same_v<T, newEntityPacket>) {
                    const newEntityPacket &newEntity = arg;
                } else if constexpr (std::is_same_v<T, deleteEntityPacket>) {
                    const deleteEntityPacket &deleteEntity = arg;
                }
            }, data.content);
    }

}// namespace cmn