/*
** EPITECH PROJECT, 2025
** R_Type
** File description:
** PositionPacket
*/

#ifndef R_TYPE_POSITIONPACKET_HPP
#define R_TYPE_POSITIONPACKET_HPP

#include <cstdint>

namespace cmn {

    struct positionPacket
    {
        uint16_t posX;
        uint16_t posY;
    };

    sf::Packet &operator << (sf::Packet &packet, const positionPacket &packetStruct);
    sf::Packet &operator >> (sf::Packet &packet, positionPacket &packetStruct);

}// namespace cmn

#endif// R_TYPE_POSITIONPACKET_HPP
