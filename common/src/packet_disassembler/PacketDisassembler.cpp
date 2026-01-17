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
#include "constants/NetworkConstants.hpp"
#include "packet_data/TextData.hpp"

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
        bool const pressed = unpacker.readBool();
        inputData data = {playerId, static_cast<cmn::Keys>(key), pressed};

        return data;
    }

    packetData PacketDisassembler::_disassembleIntoPositionData(BitUnpacker &unpacker)
    {
        std::vector<uint32_t> entityId;
        std::vector<float> posX;
        std::vector<float> posY;

        uint32_t const size = unpacker.readUInt32();


        for (size_t i = 0; i < size; i++) {
            entityId.push_back(unpacker.readUInt32());
            posX.push_back(unpacker.readFloat(0, windowWidth, xPositionFloatPrecision));
            posY.push_back(unpacker.readFloat(0, windowHeight, yPositionFloatPrecision));
        }

        positionData data = {entityId, posX, posY};

        return data;
    }

    packetData PacketDisassembler::_disassembleIntoNewEntityData(BitUnpacker &unpacker)
    {
        uint32_t const entityId = unpacker.readUInt32();
        uint8_t const entityType = unpacker.readUInt8();
        float const positionX = unpacker.readFloat(0, windowWidth, xPositionFloatPrecision);
        float const positionY = unpacker.readFloat(0, windowHeight, yPositionFloatPrecision);
        newEntityData data = {entityId, static_cast<cmn::EntityType>(entityType), positionX, positionY};

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

    packetData PacketDisassembler::_disassembleIntoStartGameData()
    {
        startGameData data = {};

        return data;
    }

    packetData PacketDisassembler::_disassembleIntoAcknowledgeData(BitUnpacker &unpacker)
    {
        uint32_t const sequenceNbr = unpacker.readUInt32();
        acknowledgeData data = {sequenceNbr};

        return data;
    }

    packetData PacketDisassembler::_disassembleIntoTextData(BitUnpacker &unpacker)
    {
        uint32_t const textId = unpacker.readUInt32();
        uint32_t const score = unpacker.readUInt32();
        textData data = {textId, score};

        return data;
    }

    std::pair<packetHeader, packetData> PacketDisassembler::disassemble(CustomPacket &packet)
    {
        std::vector<uint8_t> buffer;

        for (int i = 0; i < packet.getDataSize(); i++) {
            uint8_t byte = 0;
            packet >> byte;
            buffer.push_back(byte);
        }

        BitUnpacker unpacker(buffer, packet.getDataSize());
        uint16_t const protocolId = unpacker.readUInt16();
        uint32_t const sequenceNbr = unpacker.readUInt32();
        bool const isReliable = unpacker.readBool();

        packetHeader const header = {protocolId, sequenceNbr, isReliable};

        switch (protocolId) {
            case (connectionProtocolId):
                return {header, _disassembleIntoConnectionData(unpacker)};
            case (inputProtocolId):
                return {header, _disassembleIntoInputData(unpacker)};
            case (positionProtocolId):
                return {header, _disassembleIntoPositionData(unpacker)};
            case (newEntityProtocolId):
                return {header, _disassembleIntoNewEntityData(unpacker)};
            case (deleteEntityProtocolId):
                return {header, _disassembleIntoDeleteEntityData(unpacker)};
            case (startGameProtocolId):
                return {header, _disassembleIntoStartGameData()};
            case (soundProtocolId):
                return {header, _disassembleIntoSoundData(unpacker)};
            case (acknowledgeProtocolId):
                return {header, _disassembleIntoAcknowledgeData(unpacker)};
            case (textProtocolId):
                return  {header, _disassembleIntoTextData(unpacker)};
            default:
                throw std::exception();
        }
    }

}// namespace cmn