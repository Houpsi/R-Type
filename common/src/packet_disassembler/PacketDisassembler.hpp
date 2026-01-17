/*
** EPITECH PROJECT, 2026
** R_Type
** File description:
** PacketDisassembler
*/

#ifndef R_TYPE_PACKETDISASSEMBLER_HPP
#define R_TYPE_PACKETDISASSEMBLER_HPP

#include "bit_unpacker/BitUnpacker.hpp"
#include "custom_packet/CustomPacket.hpp"
#include "packet_data/PacketData.hpp"
#include "packet_header/PacketHeader.hpp"

namespace cmn {

    class PacketDisassembler
    {
      public:
        static std::pair<packetHeader, packetData> disassemble(CustomPacket &packet);

      private:
        static packetData _disassembleIntoConnectionData(BitUnpacker &unpacker);
        static packetData _disassembleIntoInputData(BitUnpacker &unpacker);
        static packetData _disassembleIntoPositionData(BitUnpacker &unpacker);
        static packetData _disassembleIntoNewEntityData(BitUnpacker &unpacker);
        static packetData _disassembleIntoDeleteEntityData(BitUnpacker &unpacker);
        static packetData _disassembleIntoStartGameData();
        static packetData _disassembleIntoSoundData(BitUnpacker &unpacker);
        static packetData _disassembleIntoAcknowledgeData(BitUnpacker &unpacker);
        static packetData _disassembleIntoTextData(BitUnpacker &unpacker);
        static packetData _disassembleIntoLeaveLobbyData(BitUnpacker &unpacker);
        static packetData _disassembleIntoErrorTcpData(BitUnpacker &unpacker);
        static packetData _disassembleIntoJoinLobbyData(BitUnpacker &unpacker);
        static packetData _disassembleIntoSelectModeData(BitUnpacker &unpacker);
        static packetData _disassembleIntoRequestJoinLobbyData(BitUnpacker &unpacker);
        static packetData _disassembleIntoPlayerDeathData(BitUnpacker &unpacker);
        static packetData _disassembleIntoGameResultData(BitUnpacker &unpacker);
    };

}// namespace cmn

#endif// R_TYPE_PACKETDISASSEMBLER_HPP
