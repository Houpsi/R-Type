/*
** EPITECH PROJECT, 2025
** R_Type
** File description:
** PacketFactory
*/

#ifndef R_TYPE_PACKETFACTORY_HPP
#define R_TYPE_PACKETFACTORY_HPP

#include "custom_packet/CustomPacket.hpp"
#include "enums/EntityType.hpp"
#include "enums/Key.hpp"
#include "enums/KeyState.hpp"

namespace cmn {

    class PacketFactory
    {
      public:
        static CustomPacket createInputPacket(Keys key, KeyState state, uint64_t entityId);
        static CustomPacket createPositionPacket(std::pair<float, float> positions, uint64_t entityId);
        static CustomPacket createNewEntityPacket(EntityType type, std::pair<float, float> positions, uint64_t entityId);
        static CustomPacket createDeleteEntityPacket(uint64_t entityId);

      private:

    };

}// namespace cmn

#endif// R_TYPE_PACKETFACTORY_HPP
