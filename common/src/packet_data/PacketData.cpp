/*
** EPITECH PROJECT, 2025
** R_Type
** File description:
** PacketData
*/

#include "InputPacket.hpp"
namespace cmn {
    sf::Packet &operator << (sf::Packet &packet, const inputPacket &packetStruct)
    {
        return packet << packetStruct.key << packetStruct.keyState;
    }

    sf::Packet &operator >> (sf::Packet &packet, inputPacket &packetStruct)
    {
        return packet >> packetStruct.key >> packetStruct.keyState;
    }
}