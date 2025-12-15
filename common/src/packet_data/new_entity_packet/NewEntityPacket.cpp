/*
** EPITECH PROJECT, 2025
** R_Type
** File description:
** NewEntityPacket
*/

#include "NewEntityPacket.hpp"
#include <SFML/Network/Packet.hpp>

namespace cmn {

    sf::Packet &operator << (sf::Packet &packet, const newEntityPacket &packetStruct)
    {
        return packet << packetStruct.entityId << packetStruct.type << packetStruct.posX << packetStruct.posY;
    }

    sf::Packet &operator >> (sf::Packet &packet, newEntityPacket &packetStruct)
    {
        return packet >> packetStruct.entityId >> packetStruct.type >> packetStruct.posX >> packetStruct.posY;
    }

}// namespace cmn