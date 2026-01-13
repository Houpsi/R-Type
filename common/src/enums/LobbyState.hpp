/*
** EPITECH PROJECT, 2026
** R_Type
** File description:
** LobbyState
*/

#ifndef R_TYPE_LOBBYSTATE_HPP
#define R_TYPE_LOBBYSTATE_HPP
#include <cstdint>

namespace cmn {
    enum class LobbyState : uint8_t
    {
        Waiting,
        Running,
        EndGame
    };
}

#endif// R_TYPE_LOBBYSTATE_HPP
