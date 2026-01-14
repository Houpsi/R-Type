/*
** EPITECH PROJECT, 2026
** R_Type
** File description:
** CollisionPacket
*/


#include "SoundPacket.hpp"


namespace cmn {

    sf::Packet &operator << (sf::Packet &packet, const soundPacket &packetStruct)
    {
        return packet << packetStruct.soundId;
    }

    sf::Packet &operator >> (sf::Packet &packet, soundPacket &packetStruct)
    {
        return packet >> packetStruct.soundId;
    }

}// namespace cmn