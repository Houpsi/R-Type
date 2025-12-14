/*
** EPITECH PROJECT, 2025
** R_Type
** File description:
** ConnectionPacket
*/

#include "ConnectionPacket.hpp"

namespace cmn {

    sf::Packet &operator << (sf::Packet &packet, const connectionPacket &packetStruct)
    {
        return packet << packetStruct.playerId;
    }

    sf::Packet &operator >> (sf::Packet &packet, connectionPacket &packetStruct)
    {
        return packet >> packetStruct.playerId;
    }


}// namespace cmn