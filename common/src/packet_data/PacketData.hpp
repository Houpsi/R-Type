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
#include "InputData.hpp"
#include "NewEntityData.hpp"
#include "PositionData.hpp"
#include "SoundData.hpp"
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
        acknowledgeData,
        textData
    >;

}

#endif// R_TYPE_PACKETDATA_HPP
