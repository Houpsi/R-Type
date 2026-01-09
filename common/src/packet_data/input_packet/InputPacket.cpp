/*
** EPITECH PROJECT, 2025
** R_Type
** File description:
** InputPacket
*/

#include "SFML/Network/Packet.hpp"
#include "InputPacket.hpp"

namespace cmn {

    sf::Packet &operator << (sf::Packet &packet, const inputPacket &packetStruct)
    {
        return packet << packetStruct.playerId << packetStruct.key << packetStruct.keyState;
    }

    sf::Packet &operator >> (sf::Packet &packet, inputPacket &packetStruct)
    {
        return packet >> packetStruct.playerId >> packetStruct.key >> packetStruct.keyState;
    }

}