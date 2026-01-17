/*
** EPITECH PROJECT, 2026
** R_Type
** File description:
** ProtocolConstants
*/

#ifndef R_TYPE_NETWORKCONSTANTS_HPP
#define R_TYPE_NETWORKCONSTANTS_HPP

#include <cstdint>

namespace cmn {

    constexpr int ticksBeforeResending = 200;
    constexpr uint32_t reliabilityRetries = 5;
    constexpr uint16_t maxSequences = 1000;
    constexpr int16_t maxSequenceDiff = -500;

    constexpr uint16_t connectionProtocolId = 0;
    constexpr uint16_t inputProtocolId = 1;
    constexpr uint16_t positionProtocolId = 2;
    constexpr uint16_t newEntityProtocolId = 3;
    constexpr uint16_t deleteEntityProtocolId = 4;
    constexpr uint16_t startGameProtocolId = 5;
    constexpr uint16_t soundProtocolId = 6;
    constexpr uint16_t acknowledgeProtocolId = 7;
    constexpr uint16_t leaveLobbyProtocolId = 8;
    constexpr uint16_t errorTcpProtocolId = 9;
    constexpr uint16_t joinLobbyProtocolId = 10;
    constexpr uint16_t selectModeProtocolId = 11;
    constexpr uint16_t requestJoinLobbyProtocolId = 12;
    constexpr uint16_t gameResultProtocolId = 13;
    constexpr uint16_t playerDeathProtocolId = 14;
    constexpr uint16_t textProtocolId = 15;

    // id ERROR
    constexpr uint16_t noExistentLobbyError = 0;
    constexpr uint16_t noWaitingLobby = 1;
    constexpr uint16_t fullLobbyError = 2;
}

#endif// R_TYPE_NETWORKCONSTANTS_HPP
