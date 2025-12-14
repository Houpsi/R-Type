/*
** EPITECH PROJECT, 2025
** R_Type
** File description:
** NewEntityPacket
*/

#ifndef R_TYPE_NEWENTITYPACKET_HPP
#define R_TYPE_NEWENTITYPACKET_HPP

#include <cstdint>
#include "SFML/Network/Packet.hpp"

namespace cmn {

    using newEntityPacket = struct newEntityPacket
    {
        uint8_t type;
        float posX;
        float posY;
    };

    sf::Packet &operator << (sf::Packet &packet, const newEntityPacket &packetStruct);
    sf::Packet &operator >> (sf::Packet &packet, newEntityPacket &packetStruct);

}// namespace cmn

#endif// R_TYPE_NEWENTITYPACKET_HPP
