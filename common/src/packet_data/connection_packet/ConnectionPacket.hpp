/*
** EPITECH PROJECT, 2025
** R_Type
** File description:
** ConnectionPacket
*/

#ifndef R_TYPE_CONNECTIONPACKET_HPP
#define R_TYPE_CONNECTIONPACKET_HPP

#include "SFML/Network/Packet.hpp"
#include <cstdint>
namespace cmn {

    using connectionPacket = struct ConnectionPacket
    {
        uint32_t playerId;
    };

    sf::Packet &operator << (sf::Packet &packet, const connectionPacket &packetStruct);
    sf::Packet &operator >> (sf::Packet &packet, connectionPacket &packetStruct);

}// namespace cmn

#endif// R_TYPE_CONNECTIONPACKET_HPP
