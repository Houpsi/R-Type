/*
** EPITECH PROJECT, 2025
** R_Type
** File description:
** PacketData
*/
#ifndef R_TYPE_PACKETDATA_HPP
#define R_TYPE_PACKETDATA_HPP

#include "error_tcp_data/ErrorTcpData.hpp"
#include "join_lobby_data/JoinLobbyData.hpp"
#include "leave_lobby_data/LeaveLobbyData.hpp"
#include "packet_data/connection_data/ConnectionData.hpp"
#include "packet_data/delete_entity_data/DeleteEntityData.hpp"
#include "packet_data/input_data/InputData.hpp"
#include "packet_data/new_entity_data/NewEntityData.hpp"
#include "packet_data/position_data/PositionData.hpp"
#include "packet_data/start_game_data/StartGameData.hpp"
#include "request_join_lobby_data/RequestJoinLobbyData.hpp"
#include "select_mode_data/SelectModeData.hpp"

#include <variant>

namespace cmn {

    using packetData = std::variant<
        connectionData,
        inputData,
        positionData,
        newEntityData,
        deleteEntityData,
        startGameData,
        leaveLobbyData,
        errorTcpData,
        joinLobbyData,
        selectModeData,
        requestJoinLobbyData>;
}

#endif// R_TYPE_PACKETDATA_HPP
