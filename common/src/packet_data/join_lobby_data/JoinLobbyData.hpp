/*
** EPITECH PROJECT, 2026
** R_Type
** File description:
** join_lobby_data
*/

#ifndef R_TYPE_JOIN_LOBBY_DATA_HPP
#define R_TYPE_JOIN_LOBBY_DATA_HPP
#include <cstdint>

namespace cmn {

    using joinLobbyData = struct joinLobbyData
    {
        uint32_t lobbyId;
        uint8_t lobbyType;
        uint32_t lobbyCode;
    };

}

#endif// R_TYPE_JOIN_LOBBY_DATA_HPP
