/*
** EPITECH PROJECT, 2025
** R_Type
** File description:
** StartGamePacket
*/

#ifndef R_TYPE_STARTGAMEPACKET_HPP
#define R_TYPE_STARTGAMEPACKET_HPP

#include "SFML/Network/Packet.hpp"

namespace cmn {

    using startGamePacket = struct StartGamePacket {};

    sf::Packet &operator << (sf::Packet &packet, const startGamePacket &packetStruct);
    sf::Packet &operator >> (sf::Packet &packet, startGamePacket &packetStruct);

}// namespace cmn

#endif// R_TYPE_STARTGAMEPACKET_HPP
