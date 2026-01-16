/*
** EPITECH PROJECT, 2026
** R_Type
** File description:
** BitPackingConstants
*/

#ifndef R_TYPE_BITPACKINGCONSTANTS_HPP
#define R_TYPE_BITPACKINGCONSTANTS_HPP

#include <cstdint>

namespace cmn {

    constexpr uint8_t maxBits = 32;
    constexpr uint64_t bitMask = 0xFFFFFFFF;
    constexpr uint8_t byteSize = 8;
    constexpr uint8_t lowestByteMask = 0xFF;
    constexpr uint8_t uint8Size = 8;
    constexpr uint8_t uint16Size = 16;
    constexpr uint8_t uint32Size = 32;
    constexpr uint8_t byteFiller = 7;
    constexpr uint32_t xPositionFloatPrecision = 192000;
    constexpr uint32_t yPositionFloatPrecision = 108000;

}

#endif// R_TYPE_BITPACKINGCONSTANTS_HPP
