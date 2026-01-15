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
#include "packet_data/PacketData.hpp"
#include <optional>
#include <unordered_map>

namespace cmn {

    class PacketFactory
    {
      public:
        static CustomPacket createPacket(packetData data, std::unordered_map<uint32_t, cmn::CustomPacket> &sequencePacketMap);

      private:
        static CustomPacket _createConnectionPacket(connectionData data);
        static CustomPacket _createInputPacket(inputData data);
        static CustomPacket _createPositionPacket(positionData data);
        static CustomPacket _createNewEntityPacket(newEntityData data,
            std::unordered_map<uint32_t, cmn::CustomPacket> &sequencePacketMap);
        static CustomPacket _createDeleteEntityPacket(deleteEntityData data,
            std::unordered_map<uint32_t, cmn::CustomPacket> &sequencePacketMap);
        static CustomPacket _createStartGamePacket();
        static CustomPacket _createAcknowledgePacket(acknowledgeData data);
        static CustomPacket _putInPacket(BitPacker &packer);
        static uint32_t _sequenceNbr;
    };

}// namespace cmn

#endif// R_TYPE_PACKETFACTORY_HPP
