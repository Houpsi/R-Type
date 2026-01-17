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
#include "enums/Key.hpp"
#include "enums/KeyState.hpp"

namespace cmn {

    using inputData = struct inputData
    {
        uint32_t playerId;
        Keys key;
        KeyState keyState;
    };

}

#endif// R_TYPE_INPUTDATA_HPP
