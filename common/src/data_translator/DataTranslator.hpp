/*
** EPITECH PROJECT, 2025
** R_Type
** File description:
** DataTranslator
*/

#ifndef R_TYPE_DATATRANSLATOR_HPP
#define R_TYPE_DATATRANSLATOR_HPP

#include "EcsManager.hpp"
#include "packet_data/PacketData.hpp"

namespace cmn {

    class DataTranslator
    {
      public:
        void translate(ecs::EcsManager &ecs, packetData &data);

      private:
        uint8_t _yourPlayerEntityId;
        static void _injectInput(ecs::EcsManager &ecs, inputPacket &input, int entityId);
        static void _injectPosition(ecs::EcsManager &ecs, positionPacket &position, int entityId);
        void _injectNewEntity(ecs::EcsManager &ecs, newEntityPacket &newEntity, int entityId);
        static void _deleteEntity(ecs::EcsManager &ecs, deleteEntityPacket &deleteEntity, int entityId);
    };

}// namespace cmn

#endif// R_TYPE_DATATRANSLATOR_HPP
