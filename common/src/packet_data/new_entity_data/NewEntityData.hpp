/*
** EPITECH PROJECT, 2025
** R_Type
** File description:
** NewEntityPacket
*/

#ifndef R_TYPE_NEWENTITYDATA_HPP
#define R_TYPE_NEWENTITYDATA_HPP

#include <cstdint>
#include "SFML/Network/Packet.hpp"

namespace cmn {

    using newEntityData = struct newEntityData
    {
        uint64_t entityId;
        uint8_t type;
        float posX;
        float posY;
    };

}// namespace cmn

#endif// R_TYPE_NEWENTITYDATA_HPP
