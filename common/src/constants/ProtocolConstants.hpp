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
    constexpr uint16_t leaveLobbyProtocolId = 6;
    constexpr uint16_t errorTcpProtocolId = 7;
    constexpr uint16_t joinLobbyProtocolId = 8;
    constexpr uint16_t selectModeProtocolId = 9;
    constexpr uint16_t requestJoinLobbyProtocolId = 10;

    // id ERROR
    constexpr uint16_t noExistentLobbyError = 0;
    constexpr uint16_t noWaitingLobby = 1;
    constexpr uint16_t fullLobbyError = 2;
}

#endif// R_TYPE_PROTOCOLCONSTANTS_HPP
