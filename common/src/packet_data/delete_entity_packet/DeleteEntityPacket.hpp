/*
** EPITECH PROJECT, 2025
** R_Type
** File description:
** DeleteEntityPacket
*/

#ifndef R_TYPE_DELETEENTITYPACKET_HPP
#define R_TYPE_DELETEENTITYPACKET_HPP

#include <SFML/Network/Packet.hpp>
#include <cstdint>
namespace cmn {

    using deleteEntityPacket = struct deleteEntityPacket
    {
        uint8_t easterEgg;
    };

    sf::Packet &operator << (sf::Packet &packet, const deleteEntityPacket &packetStruct);
    sf::Packet &operator >> (sf::Packet &packet, deleteEntityPacket &packetStruct);

}// namespace cmn

#endif// R_TYPE_DELETEENTITYPACKET_HPP
