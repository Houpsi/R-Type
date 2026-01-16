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
        static CustomPacket createLeaveLobbyPacket(uint32_t playerId);
        static CustomPacket createErrorTcpPacket(uint8_t errorId);
        static CustomPacket createJoinLobbyPacket(uint32_t lobbyId, uint8_t lobbyType, uint32_t lobbyCode);
        static CustomPacket createSelectModePacket(uint8_t lobbyType, uint32_t playerId);
        static CustomPacket createRequestJoinLobbyPacket(uint32_t playerId, uint32_t lobbyCode);

      private:
        static CustomPacket _putInPacket(BitPacker &packer);
    };

}// namespace cmn

#endif// R_TYPE_PACKETFACTORY_HPP
