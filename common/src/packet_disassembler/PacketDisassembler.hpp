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
#include <optional>

namespace cmn {

    class PacketDisassembler
    {
      public:
        static std::optional<packetData> disassemble(CustomPacket &packet);

      private:
        static packetData _disassembleIntoConnectionData(cmn::BitUnpacker &unpacker);
        static packetData _disassembleIntoInputData(BitUnpacker &unpacker);
        static packetData _disassembleIntoPositionData(BitUnpacker &unpacker);
        static packetData _disassembleIntoNewEntityData(BitUnpacker &unpacker);
        static packetData _disassembleIntoDeleteEntityData(BitUnpacker &unpacker);
        static packetData _disassembleIntoStartGameData(BitUnpacker &unpacker);
        static packetData _disassembleIntoSoundData(BitUnpacker &unpacker);

    };

}// namespace cmn

#endif// R_TYPE_PACKETDISASSEMBLER_HPP
