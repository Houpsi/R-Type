/*
** EPITECH PROJECT, 2026
** R_Type
** File description:
** SelectModeData
*/

#ifndef R_TYPE_SELECTMODEDATA_HPP
#define R_TYPE_SELECTMODEDATA_HPP
#include <cstdint>
#include <string>

namespace cmn {

    using selectModeData = struct selectModeData
    {
        uint8_t lobbyType;
        uint32_t playerId;
    };

}

#endif// R_TYPE_SELECTMODEDATA_HPP
