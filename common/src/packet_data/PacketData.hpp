/*
** EPITECH PROJECT, 2025
** R_Type
** File description:
** PacketData
*/
#ifndef R_TYPE_PACKETDATA_HPP
#define R_TYPE_PACKETDATA_HPP

#include "packet_data/delete_entity_packet/DeleteEntityPacket.hpp"
#include "packet_data/input_packet/InputPacket.hpp"
#include "packet_data/new_entity_packet/NewEntityPacket.hpp"
#include "packet_data/position_packet/PositionPacket.hpp"
#include <variant>

namespace cmn {

    using packetContent = std::variant<inputPacket, positionPacket, newEntityPacket, deleteEntityPacket>;

    using packetData = struct packetData {
        uint16_t packetId;
        uint64_t entityId;
        packetContent content;
    };

    sf::Packet &operator << (sf::Packet &packet, const packetContent &content);
    sf::Packet &operator >> (sf::Packet &packet, packetContent &data);
    sf::Packet &operator << (sf::Packet &packet, const packetData &data);
    sf::Packet &operator >> (sf::Packet &packet, packetData &data);

}

#endif// R_TYPE_PACKETDATA_HPP
