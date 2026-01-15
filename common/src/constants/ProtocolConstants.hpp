/*
** EPITECH PROJECT, 2026
** R_Type
** File description:
** ProtocolConstants
*/

#ifndef R_TYPE_PROTOCOLCONSTANTS_HPP
#define R_TYPE_PROTOCOLCONSTANTS_HPP

#include <cstdint>

namespace cmn {

    constexpr uint16_t connectionProtocolId = 0;
    constexpr uint16_t inputProtocolId = 1;
    constexpr uint16_t positionProtocolId = 2;
    constexpr uint16_t newEntityProtocolId = 3;
    constexpr uint16_t deleteEntityProtocolId = 4;
    constexpr uint16_t startGameProtocolId = 5;
    constexpr uint16_t soundProtocolId = 6;


}

#endif// R_TYPE_PROTOCOLCONSTANTS_HPP
