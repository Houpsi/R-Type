/*
** EPITECH PROJECT, 2026
** R_Type
** File description:
** CollisionPacket
*/

#ifndef R_TYPE_COLLISIONPACKET_HPP
#define R_TYPE_COLLISIONPACKET_HPP

#include <SFML/Network/Packet.hpp>
#include <cstdint>

namespace cmn {

    using soundData = struct soundPacket {
        uint8_t soundId;
    };
}// namespace cmn

#endif// R_TYPE_COLLISIONPACKET_HPP
