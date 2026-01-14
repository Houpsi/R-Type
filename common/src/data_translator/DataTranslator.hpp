/*
** EPITECH PROJECT, 2025
** R_Type
** File description:
** DataTranslator
*/

#ifndef R_TYPE_DATATRANSLATOR_HPP
#define R_TYPE_DATATRANSLATOR_HPP

#include "managers/EcsManager.hpp"
#include "packet_data/PacketData.hpp"

namespace cmn {

    class DataTranslator
    {
      public:
        static void translate(ecs::EcsManager &ecs, packetData &data, const std::unordered_map<int, uint64_t>& playerIdEntityMap);

      private:
        static void _injectInput(ecs::EcsManager &ecs, inputData &input, std::unordered_map<int, uint64_t> playerIdEntityMap);
        static void _injectPosition(ecs::EcsManager &ecs, positionData &position);
        static void _injectNewEntity(ecs::EcsManager &ecs, newEntityData &newEntity);
        static void _deleteEntity(ecs::EcsManager &ecs, deleteEntityData &deleteEntity);
    };

}// namespace cmn

#endif// R_TYPE_DATATRANSLATOR_HPP
