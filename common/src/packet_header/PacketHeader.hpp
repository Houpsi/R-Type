/*
** EPITECH PROJECT, 2026
** R_Type
** File description:
** PacketHeader
*/

#ifndef R_TYPE_PACKETHEADER_HPP
#define R_TYPE_PACKETHEADER_HPP

#include <cstdint>
namespace cmn {

    using packetHeader = struct packetHeader
    {
        uint16_t protocolId;
        uint32_t sequenceNbr;
        bool isReliable;
    };

}

#endif// R_TYPE_PACKETHEADER_HPP
