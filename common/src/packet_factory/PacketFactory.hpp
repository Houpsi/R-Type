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
#include "bit_packer/BitPacker.hpp"

namespace cmn {

    class PacketFactory
    {
      public:
        static CustomPacket createConnectionPacket(uint32_t playerId);
        static CustomPacket createInputPacket(uint32_t playerId, Keys key, KeyState state);
        static CustomPacket createPositionPacket(std::pair<float, float> positions, uint64_t entityId);
        static CustomPacket createNewEntityPacket(EntityType type, std::pair<float, float> positions, uint64_t entityId);
        static CustomPacket createDeleteEntityPacket(uint64_t entityId);
        static CustomPacket createStartGamePacket();

      private:
        static CustomPacket _putInPacket(BitPacker &packer);
    };

}// namespace cmn

#endif// R_TYPE_PACKETFACTORY_HPP
