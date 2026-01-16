/*
** EPITECH PROJECT, 2025
** R_Type
** File description:
** PositionPacket
*/

#ifndef R_TYPE_POSITIONDATA_HPP
#define R_TYPE_POSITIONDATA_HPP

#include <cstdint>
#include "SFML/Network/Packet.hpp"

namespace cmn {

    using positionData = struct positionData
    {
        uint32_t entityId;
        float posX;
        float posY;
    };

}// namespace cmn

#endif// R_TYPE_POSITIONDATA_HPP
