/*
** EPITECH PROJECT, 2026
** R_Type
** File description:
** LobbyType
*/

#ifndef R_TYPE_LOBBYTYPE_HPP
#define R_TYPE_LOBBYTYPE_HPP
#include <cstdint>

namespace cmn {
    enum LobbyType: uint8_t {
        Solo,
        Lobby,
        Matchmaking
    };
}

#endif// R_TYPE_LOBBYTYPE_HPP
