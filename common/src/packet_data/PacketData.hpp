/*
** EPITECH PROJECT, 2025
** R_Type
** File description:
** PacketData
*/
#ifndef R_TYPE_PACKETDATA_HPP
#define R_TYPE_PACKETDATA_HPP

#include "packet_data/connection_data/ConnectionData.hpp"
#include "packet_data/delete_entity_data/DeleteEntityData.hpp"
#include "packet_data/input_data/InputData.hpp"
#include "packet_data/new_entity_data/NewEntityData.hpp"
#include "packet_data/position_data/PositionData.hpp"
#include "packet_data/start_game_data/StartGameData.hpp"
#include <variant>

namespace cmn {

    using packetData = std::variant<connectionData, inputData, positionData, newEntityData, deleteEntityData, startGameData>;
}

#endif// R_TYPE_PACKETDATA_HPP
