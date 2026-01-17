/*
** EPITECH PROJECT, 2026
** r-type_client
** File description:
** TextPacket
*/
#ifndef R_TYPE_CLIENT_TEXTPACKET_HPP
#define R_TYPE_CLIENT_TEXTPACKET_HPP
#include <cstdint>

namespace cmn
{
    using textData = struct TextPacket {
        uint32_t entityId;
        uint32_t score;
    };
}

#endif //R_TYPE_CLIENT_TEXTPACKET_HPP