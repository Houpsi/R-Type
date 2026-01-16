/*
** EPITECH PROJECT, 2026
** R_Type
** File description:
** PacketDisassembler
*/

#include "PacketDisassembler.hpp"
#include "bit_unpacker/BitUnpacker.hpp"
#include "constants/BitPackingConstants.hpp"
#include "constants/GameConstants.hpp"
#include "constants/ProtocolConstants.hpp"
#include <optional>

namespace cmn {

    packetData PacketDisassembler::_disassembleIntoConnectionData(BitUnpacker &unpacker)
    {
        uint32_t const playerId = unpacker.readUInt32();
        connectionData data = {playerId};

        return data;
    }

    packetData PacketDisassembler::_disassembleIntoInputData(BitUnpacker &unpacker)
    {
        uint32_t const playerId = unpacker.readUInt32();
        uint8_t const key = unpacker.readUInt8();
        uint8_t const keyState = unpacker.readUInt8();
        inputData data = {playerId, key, keyState};

        return data;
    }

    packetData PacketDisassembler::_disassembleIntoPositionData(BitUnpacker &unpacker)
    {
        uint32_t const entityId = unpacker.readUInt32();
        float const positionX = unpacker.readFloat(0, windowWidth, xPositionFloatPrecision);
        float const positionY = unpacker.readFloat(0, windowHeight, yPositionFloatPrecision);
        positionData data = {entityId, positionX, positionY};

        return data;
    }

    packetData PacketDisassembler::_disassembleIntoNewEntityData(BitUnpacker &unpacker)
    {
        uint32_t const entityId = unpacker.readUInt32();
        uint8_t const entityType = unpacker.readUInt8();
        float const positionX = unpacker.readFloat(0, windowWidth, xPositionFloatPrecision);
        float const positionY = unpacker.readFloat(0, windowHeight, yPositionFloatPrecision);
        newEntityData data = {entityId, entityType, positionX, positionY};

        return data;
    }

    packetData PacketDisassembler::_disassembleIntoDeleteEntityData(BitUnpacker &unpacker)
    {
        uint32_t const entityId = unpacker.readUInt32();
        deleteEntityData data = {entityId};

        return data;
    }

    packetData PacketDisassembler::_disassembleIntoSoundData(BitUnpacker &unpacker)
    {
        uint8_t const soundId = unpacker.readUInt8();
        soundData data = {soundId};

        return data;
    }

    packetData PacketDisassembler::_disassembleIntoStartGameData(BitUnpacker &unpacker)
    {
        startGameData data = {};

        return data;
    }

    std::optional<packetData> PacketDisassembler::disassemble(CustomPacket &packet)
    {
        std::vector<uint8_t> buffer;

        for (int i = 0; i < packet.getDataSize(); i++) {
            uint8_t byte = 0;
            packet >> byte;
            buffer.push_back(byte);
        }

        BitUnpacker unpacker(buffer, packet.getDataSize());
        uint16_t const protocolId = unpacker.readUInt16();

        switch (protocolId) {
            case (connectionProtocolId):
                return _disassembleIntoConnectionData(unpacker);
            case (inputProtocolId):
                return _disassembleIntoInputData(unpacker);
            case (positionProtocolId):
                return _disassembleIntoPositionData(unpacker);
            case (newEntityProtocolId):
                return _disassembleIntoNewEntityData(unpacker);
            case (deleteEntityProtocolId):
                return _disassembleIntoDeleteEntityData(unpacker);
            case (startGameProtocolId):
                return _disassembleIntoStartGameData(unpacker);
            case (soundProtocolId):
                return _disassembleIntoSoundData(unpacker);
            default:
                return std::nullopt;
        }
    }

}// namespace cmn