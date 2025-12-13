/*
** EPITECH PROJECT, 2025
** R_Type
** File description:
** InputPacket
*/
#ifndef R_TYPE_INPUTPACKET_HPP
#define R_TYPE_INPUTPACKET_HPP

#include "SFML/Network/Packet.hpp"
#include <cstdint>

namespace cmn {

    using inputPacket = struct inputPacket
    {
        uint8_t key;
        uint8_t keyState;
    };

    sf::Packet &operator << (sf::Packet &packet, const inputPacket &packetStruct)
    {
        return packet << packetStruct.key << packetStruct.keyState;
    }

    sf::Packet &operator >> (sf::Packet &packet, inputPacket &packetStruct)
    {
        return packet >> packetStruct.key >> packetStruct.keyState;
    }

}

#endif// R_TYPE_INPUTPACKET_HPP
