/*
** EPITECH PROJECT, 2025
** R_Type
** File description:
** PacketFactory
*/

#include "PacketFactory.hpp"
#include "constants/BitPackingConstants.hpp"
#include "constants/GameConstants.hpp"
#include "constants/NetworkConstants.hpp"

namespace cmn {

    uint32_t PacketFactory::_udpSequenceNbr = 1;
    uint32_t PacketFactory::_tcpSequenceNbr = 1;

    CustomPacket PacketFactory::_putInPacket(BitPacker &packer)
    {
        auto buffer = packer.getBuffer();
        CustomPacket packet;

        for (auto &data : buffer) {
            packet << data;
        }
        return packet;
    }

    void PacketFactory::_handleReliability(CustomPacket &packet,
        std::unordered_map<uint32_t, reliablePacket> &reliablePackets)
    {
        auto now = std::chrono::steady_clock::now();
        reliablePacket const reliablePacket = {packet, now, 0};
        reliablePackets[_udpSequenceNbr] = reliablePacket;
    }

    CustomPacket PacketFactory::_createConnectionPacket(connectionData data)
    {
        BitPacker packer;

        packer.writeUInt16(connectionProtocolId);
        packer.writeUInt32(_tcpSequenceNbr);
        packer.writeBool(false);
        packer.writeUInt32(data.playerId);

        _tcpSequenceNbr++;
        return _putInPacket(packer);
    }

    CustomPacket PacketFactory::_createInputPacket(inputData data)
    {
        BitPacker packer;

        packer.writeUInt16(inputProtocolId);
        packer.writeUInt32(_udpSequenceNbr);
        packer.writeBool(false);
        packer.writeUInt32(data.playerId);
        packer.writeUInt8(static_cast<uint8_t>(data.key));
        packer.writeBool(data.pressed);

        _udpSequenceNbr++;
        return _putInPacket(packer);
    }

    CustomPacket PacketFactory::_createPositionPacket(positionData data)
    {
        BitPacker packer;

        packer.writeUInt16(positionProtocolId);
        packer.writeUInt32(_udpSequenceNbr);
        packer.writeBool(false);
        size_t const size = data.entityId.size();
        packer.writeUInt32(size);
        for (size_t i = 0; i < size; i++) {
            packer.writeUInt32(data.entityId[i]);
            packer.writeFloat(data.posX[i], 0, windowWidth, xPositionFloatPrecision);
            packer.writeFloat(data.posY[i], 0, windowHeight, yPositionFloatPrecision);
        }
        _udpSequenceNbr++;
        return _putInPacket(packer);
    }

    CustomPacket PacketFactory::_createNewEntityPacket(newEntityData data,
        std::unordered_map<uint32_t, cmn::reliablePacket> &reliablePackets)
    {
        BitPacker packer;

        packer.writeUInt16(newEntityProtocolId);
        packer.writeUInt32(_udpSequenceNbr);
        packer.writeBool(true);
        packer.writeUInt32(data.entityId);
        packer.writeUInt8(static_cast<uint8_t>(data.type));
        packer.writeFloat(data.posX, 0, windowWidth, xPositionFloatPrecision);
        packer.writeFloat(data.posY, 0, windowHeight, yPositionFloatPrecision);

        CustomPacket packet = _putInPacket(packer);
        _handleReliability(packet, reliablePackets);

        _udpSequenceNbr++;
        return packet;
    }

    CustomPacket PacketFactory::_createDeleteEntityPacket(deleteEntityData data,
        std::unordered_map<uint32_t, cmn::reliablePacket> &reliablePackets)
    {
        BitPacker packer;

        packer.writeUInt16(deleteEntityProtocolId);
        packer.writeUInt32(_udpSequenceNbr);
        packer.writeBool(true);
        packer.writeUInt32(data.entityId);

        CustomPacket packet = _putInPacket(packer);
        _handleReliability(packet, reliablePackets);

        _udpSequenceNbr++;
        return packet;
    }

    CustomPacket PacketFactory::_createStartGamePacket()
    {
        BitPacker packer;

        packer.writeUInt16(startGameProtocolId);
        packer.writeUInt32(_tcpSequenceNbr);
        packer.writeBool(false);

        _tcpSequenceNbr++;
        return _putInPacket(packer);
    }


    CustomPacket PacketFactory::_createSoundPacket(soundData data)
    {
        BitPacker packer;

        packer.writeUInt16(soundProtocolId);
        packer.writeUInt32(_udpSequenceNbr);
        packer.writeBool(false);
        packer.writeUInt8(data.soundId);

        _udpSequenceNbr++;
        return _putInPacket(packer);
    }

    CustomPacket PacketFactory::_createAcknowledgePacket(acknowledgeData data)
    {
        BitPacker packer;

        packer.writeUInt16(acknowledgeProtocolId);
        packer.writeUInt32(_udpSequenceNbr);
        packer.writeBool(false);
        packer.writeUInt32(data.sequenceNbr);

        _udpSequenceNbr++;
        return _putInPacket(packer);
    }

    CustomPacket PacketFactory::_createTextPacket(textData data)
    {
        BitPacker packer;
        packer.writeUInt16(textProtocolId);
        packer.writeUInt32(_udpSequenceNbr);
        packer.writeBool(false);

        packer.writeUInt32(data.entityId);
        packer.writeUInt32(data.score);

        _udpSequenceNbr++;
        return _putInPacket(packer);
    }

    CustomPacket PacketFactory::createPacket(packetData data,
        std::unordered_map<uint32_t, cmn::reliablePacket> &reliablePackets)
    {
        return std::visit([&reliablePackets](auto &&arg)
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
                    return _createNewEntityPacket(newEntityData, reliablePackets);
                } else if constexpr (std::is_same_v<T, deleteEntityData>) {
                    deleteEntityData const &deleteEntityData = arg;
                    return _createDeleteEntityPacket(deleteEntityData, reliablePackets);
                } else if constexpr (std::is_same_v<T, startGameData>) {
                    return _createStartGamePacket();
                } else if constexpr (std::is_same_v<T, acknowledgeData>) {
                    acknowledgeData const &acknowledgeData = arg;
                    return _createAcknowledgePacket(acknowledgeData);
                } else if constexpr (std::is_same_v<T, soundData>) {
                    soundData const &soundData = arg;
                    return _createSoundPacket(soundData);
                } else if constexpr (std::is_same_v<T, textData>) {
                    textData const &textData = arg;
                    return _createTextPacket(textData);
                }
            }, data);
    }

}// namespace cmn