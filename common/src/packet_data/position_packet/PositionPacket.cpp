/*
** EPITECH PROJECT, 2025
** R_Type
** File description:
** PositionPacket
*/

#include "PositionPacket.hpp"
#include "SFML/Network/Packet.hpp"

namespace cmn {

    sf::Packet &operator << (sf::Packet &packet, const positionPacket &packetStruct)
    {
        return packet << packetStruct.entityId << packetStruct.posX << packetStruct.posY;
    }

    sf::Packet &operator >> (sf::Packet &packet, positionPacket &packetStruct)
    {
        return packet >> packetStruct.entityId >> packetStruct.posX >> packetStruct.posY;
    }

}// namespace cmn