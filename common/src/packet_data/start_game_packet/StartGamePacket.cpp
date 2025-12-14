/*
** EPITECH PROJECT, 2025
** R_Type
** File description:
** StartGamePacket
*/


#include "StartGamePacket.hpp"

namespace cmn {

    sf::Packet &operator << (sf::Packet &packet, const startGamePacket &packetStruct)
    {
        (void)packetStruct;
        return packet;
    }

    sf::Packet &operator >> (sf::Packet &packet, startGamePacket &packetStruct)
    {
        (void)packetStruct;
        return packet;
    }

}// namespace cmn