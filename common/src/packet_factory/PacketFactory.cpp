/*
** EPITECH PROJECT, 2025
** R_Type
** File description:
** PacketFactory
*/

#include "PacketFactory.hpp"
#include "constants/ProtocolConstants.hpp"
#include "constants/GameConstants.hpp"
#include "constants/BitPackingConstants.hpp"

namespace cmn {

    uint32_t PacketFactory::_sequenceNbr = 0;

    CustomPacket PacketFactory::_putInPacket(BitPacker &packer)
    {
        auto buffer = packer.getBuffer();
        CustomPacket packet;

        for (auto &data : buffer) {
            packet << data;
        }
        return packet;
    }

    CustomPacket PacketFactory::_createConnectionPacket(connectionData data)
    {
        BitPacker packer;

        packer.writeUInt16(connectionProtocolId);
        packer.writeUInt32(_sequenceNbr);
        packer.writeBool(false);
        packer.writeUInt32(data.playerId);

        _sequenceNbr++;
        return _putInPacket(packer);
    }

    CustomPacket PacketFactory::_createInputPacket(inputData data)
    {
        BitPacker packer;

        packer.writeUInt16(inputProtocolId);
        packer.writeUInt32(_sequenceNbr);
        packer.writeBool(false);
        packer.writeUInt32(data.playerId);
        packer.writeUInt8(static_cast<uint8_t>(data.key));
        packer.writeUInt8(static_cast<uint8_t>(data.keyState));

        _sequenceNbr++;
        return _putInPacket(packer);
    }

    CustomPacket PacketFactory::_createPositionPacket(positionData data)
    {
        BitPacker packer;

        packer.writeUInt16(positionProtocolId);
        packer.writeUInt32(_sequenceNbr);
        packer.writeBool(false);
        packer.writeUInt32(data.entityId);
        packer.writeFloat(data.posX, 0, windowWidth, xPositionFloatPrecision);
        packer.writeFloat(data.posY, 0, windowHeight, yPositionFloatPrecision);

        _sequenceNbr++;
        return _putInPacket(packer);
    }

    CustomPacket PacketFactory::_createNewEntityPacket(newEntityData data,
        std::unordered_map<uint32_t, cmn::CustomPacket> &sequencePacketMap)
    {
        BitPacker packer;

        packer.writeUInt16(newEntityProtocolId);
        packer.writeUInt32(_sequenceNbr);
        packer.writeBool(true);
        packer.writeUInt32(data.entityId);
        packer.writeUInt8(static_cast<uint8_t>(data.type));
        packer.writeFloat(data.posX, 0, windowWidth, xPositionFloatPrecision);
        packer.writeFloat(data.posY, 0, windowHeight, yPositionFloatPrecision);

        CustomPacket packet = _putInPacket(packer);

        sequencePacketMap[_sequenceNbr] = packet;
        _sequenceNbr++;
        return packet;
    }

    CustomPacket PacketFactory::_createDeleteEntityPacket(deleteEntityData data,
        std::unordered_map<uint32_t, cmn::CustomPacket> &sequencePacketMap)
    {
        BitPacker packer;

        packer.writeUInt16(deleteEntityProtocolId);
        packer.writeUInt32(_sequenceNbr);
        packer.writeBool(true);
        packer.writeUInt32(data.entityId);

        CustomPacket packet = _putInPacket(packer);

        sequencePacketMap[_sequenceNbr] = packet;
        _sequenceNbr++;
        return packet;
    }

    CustomPacket PacketFactory::_createStartGamePacket()
    {
        BitPacker packer;

        packer.writeUInt16(startGameProtocolId);
        packer.writeUInt32(_sequenceNbr);
        packer.writeBool(false);

        _sequenceNbr++;
        return _putInPacket(packer);
    }

    CustomPacket PacketFactory::_createAcknowledgePacket(acknowledgeData data)
    {
        BitPacker packer;

        packer.writeUInt16(startGameProtocolId);
        packer.writeUInt32(_sequenceNbr);
        packer.writeBool(false);
        packer.writeUInt32(data.sequenceNbr);

        _sequenceNbr++;
        return _putInPacket(packer);
    }

    CustomPacket PacketFactory::createPacket(packetData data,
        std::unordered_map<uint32_t, cmn::CustomPacket> &sequencePacketMap)
    {
        return std::visit([&sequencePacketMap](auto &&arg)
            {
                using T = std::decay_t<decltype(arg)>;
                if constexpr (std::is_same_v<T, connectionData>) {
                    connectionData const &connectionData = arg;
                    return _createConnectionPacket(connectionData);
                } else if constexpr (std::is_same_v<T, inputData>) {
                    inputData const &inputData = arg;
                    return _createInputPacket(inputData);
                } else if constexpr (std::is_same_v<T, positionData>) {
                    positionData const &positionData = arg;
                    return _createPositionPacket(positionData);
                } else if constexpr (std::is_same_v<T, newEntityData>) {
                    newEntityData const &newEntityData = arg;
                    return _createNewEntityPacket(newEntityData, sequencePacketMap);
                } else if constexpr (std::is_same_v<T, deleteEntityData>) {
                    deleteEntityData const &deleteEntityData = arg;
                    return _createDeleteEntityPacket(deleteEntityData, sequencePacketMap);
                } else if constexpr (std::is_same_v<T, startGameData>) {
                    return _createStartGamePacket();
                } else if constexpr (std::is_same_v<T, acknowledgeData>) {
                    acknowledgeData const &acknowledgeData = arg;
                    return _createAcknowledgePacket(acknowledgeData);
                }
            }, data);
    }

}// namespace cmn