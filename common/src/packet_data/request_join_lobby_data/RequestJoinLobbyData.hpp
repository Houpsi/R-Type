/*
** EPITECH PROJECT, 2026
** R_Type
** File description:
** RequestJoinLobbyData
*/

#ifndef R_TYPE_REQUESTJOINLOBBYDATA_HPP
#define R_TYPE_REQUESTJOINLOBBYDATA_HPP
#include <cstdint>

namespace cmn {

    using requestJoinLobbyData = struct requestJoinLobbyData
    {
        uint32_t playerId;
        uint32_t lobbyCode;
    };
}

#endif// R_TYPE_REQUESTJOINLOBBYDATA_HPP
