/*
** EPITECH PROJECT, 2025
** R_Type
** File description:
** PositionPacket
*/

#ifndef R_TYPE_POSITIONPACKET_HPP
#define R_TYPE_POSITIONPACKET_HPP

#include <cstdint>
#include "SFML/Network/Packet.hpp"

namespace cmn {

    struct positionPacket
    {
        float posX;
        float posY;
    };

    sf::Packet &operator << (sf::Packet &packet, const positionPacket &packetStruct);
    sf::Packet &operator >> (sf::Packet &packet, positionPacket &packetStruct);

}// namespace cmn

#endif// R_TYPE_POSITIONPACKET_HPP
