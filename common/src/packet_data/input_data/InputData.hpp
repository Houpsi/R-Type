/*
** EPITECH PROJECT, 2025
** R_Type
** File description:
** InputPacket
*/
#ifndef R_TYPE_INPUTDATA_HPP
#define R_TYPE_INPUTDATA_HPP

#include "SFML/Network/Packet.hpp"
#include <cstdint>

namespace cmn {

    using inputData = struct inputData
    {
        uint32_t playerId;
        uint8_t key;
        uint8_t keyState;
    };

}

#endif// R_TYPE_INPUTDATA_HPP
