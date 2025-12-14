/*
** EPITECH PROJECT, 2025
** R_Type
** File description:
** DeleteEntityPacket
*/

#include "DeleteEntityPacket.hpp"

namespace cmn {

    sf::Packet &operator << (sf::Packet &packet, const deleteEntityPacket &packetStruct)
    {
        return packet << packetStruct.entityId;
    }

    sf::Packet &operator >> (sf::Packet &packet, deleteEntityPacket &packetStruct)
    {
        return packet >> packetStruct.entityId;
    }

}// namespace cmn