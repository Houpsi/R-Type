/*
** EPITECH PROJECT, 2025
** R_Type
** File description:
** PacketData
*/
#ifndef R_TYPE_PACKETDATA_HPP
#define R_TYPE_PACKETDATA_HPP

#include "AcknowledgeData.hpp"
#include "ConnectionData.hpp"
#include "DeleteEntityData.hpp"
#include "ErrorTcpData.hpp"
#include "GameResultData.hpp"
#include "InputData.hpp"
#include "JoinLobbyData.hpp"
#include "LeaveLobbyData.hpp"
#include "NewEntityData.hpp"
#include "PlayerDeathData.hpp"
#include "PositionData.hpp"
#include "RequestJoinLobbyData.hpp"
#include "SelectModeData.hpp"
#include "SoundData.hpp"
#include "StartGameData.hpp"
#include "StartGameData.hpp"
#include "TextData.hpp"

#include <variant>

namespace cmn {

    using packetData = std::variant<
        connectionData,
        inputData,
        positionData,
        newEntityData,
        deleteEntityData,
        startGameData,
        soundData,
        textData,
        acknowledgeData,
        leaveLobbyData,
        errorTcpData,
        joinLobbyData,
        selectModeData,
        requestJoinLobbyData,
        playerDeathData,
        gameResultData
    >;
}

#endif// R_TYPE_PACKETDATA_HPP
