/*
** EPITECH PROJECT, 2025
** R_Type
** File description:
** PacketFactory
*/

#ifndef R_TYPE_PACKETFACTORY_HPP
#define R_TYPE_PACKETFACTORY_HPP

#include "bit_packer/BitPacker.hpp"
#include "custom_packet/CustomPacket.hpp"
#include "enums/EntityType.hpp"
#include "enums/Key.hpp"
#include "packet_data/PacketData.hpp"
#include "packet_data/TextData.hpp"
#include "reliable_packet/ReliablePacket.hpp"
#include <optional>
#include <unordered_map>

namespace cmn {

    class PacketFactory
    {
      public:
        static CustomPacket createPacket(packetData data, std::unordered_map<uint32_t, reliablePacket> &reliablePackets);

      private:
        static CustomPacket _createConnectionPacket(connectionData data);
        static CustomPacket _createInputPacket(inputData data);
        static CustomPacket _createPositionPacket(positionData data);
        static CustomPacket _createNewEntityPacket(newEntityData data,
            std::unordered_map<uint32_t, reliablePacket> &reliablePackets);
        static CustomPacket _createDeleteEntityPacket(deleteEntityData data,
            std::unordered_map<uint32_t, reliablePacket> &reliablePackets);
        static CustomPacket _createStartGamePacket();
        static CustomPacket _createAcknowledgePacket(acknowledgeData data);
        static CustomPacket _putInPacket(BitPacker &packer);
        static CustomPacket _createSoundPacket(soundData data);
        static CustomPacket _createLeaveLobbyPacket(leaveLobbyData data);
        static CustomPacket _createErrorTcpPacket(errorTcpData data);
        static CustomPacket _createJoinLobbyPacket(joinLobbyData data);
        static CustomPacket _createSelectModePacket(selectModeData data);
        static CustomPacket _createRequestJoinLobbyPacket(requestJoinLobbyData data);
        static CustomPacket _createPlayerDeathPacket(playerDeathData data);
        static CustomPacket _createGameResultPacket(gameResultData data);
        static CustomPacket _createTextPacket(textData data);
        static void _handleReliability(CustomPacket &packet, std::unordered_map<uint32_t, reliablePacket> &reliablePackets);

        static uint32_t _udpSequenceNbr;
        static uint32_t _tcpSequenceNbr;
    };

}// namespace cmn

#endif// R_TYPE_PACKETFACTORY_HPP
