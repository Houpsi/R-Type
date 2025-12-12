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

    sf::Packet &operator << (sf::Packet &packet, const packetContent &content)
    {
        packet << content.index();

        std::visit([&packet](auto &&arg) {
            packet << arg;
        }, content);

        return packet;
    }

    sf::Packet &operator >> (sf::Packet &packet, packetContent &data)
    {
        std::size_t typeIndex = 0;
        packet >> typeIndex;

        switch (typeIndex) {
            case 0: {
                inputPacket input;
                packet >> input;
                data = input;
                break;
            }
            default: {
                throw std::exception();
            }
        }

        return packet;
    }

    sf::Packet &operator << (sf::Packet &packet, const packetData &data)
    {
        return packet << data.packetId << data.content;
    }

    sf::Packet &operator >> (sf::Packet &packet, packetData &data)
    {
        return packet >> data.packetId >> data.content;
    }

}

#endif// R_TYPE_PACKETDATA_HPP
