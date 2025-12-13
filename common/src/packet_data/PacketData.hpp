/*
** EPITECH PROJECT, 2025
** R_Type
** File description:
** PacketData
*/
#ifndef R_TYPE_PACKETDATA_HPP
#define R_TYPE_PACKETDATA_HPP

#include "InputPacket.hpp"
#include <variant>

namespace cmn {

    using packetContent = std::variant<inputPacket>;

    using packetData = struct packetData {
        int packetId;
        packetContent content;
    };

    sf::Packet &operator << (sf::Packet &packet, const packetContent &content);
    sf::Packet &operator >> (sf::Packet &packet, packetContent &data);
    sf::Packet &operator << (sf::Packet &packet, const packetData &data);
    sf::Packet &operator >> (sf::Packet &packet, packetData &data);

}

#endif// R_TYPE_PACKETDATA_HPP
