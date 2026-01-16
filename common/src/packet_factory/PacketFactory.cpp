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

#include <bits/codecvt.h>

namespace cmn {

    CustomPacket PacketFactory::_putInPacket(BitPacker &packer)
    {
        auto buffer = packer.getBuffer();
        CustomPacket packet;

        for (auto &data : buffer) {
            packet << data;
        }
        return packet;
    }

    CustomPacket PacketFactory::createConnectionPacket(uint32_t playerId)
    {
        BitPacker packer;

        packer.writeUInt16(connectionProtocolId);
        packer.writeUInt32(playerId);

        return _putInPacket(packer);
    }

    CustomPacket PacketFactory::createInputPacket(uint32_t playerId, Keys key, KeyState state)
    {
        BitPacker packer;

        packer.writeUInt16(inputProtocolId);
        packer.writeUInt32(playerId);
        packer.writeUInt8(static_cast<uint8_t>(key));
        packer.writeUInt8(static_cast<uint8_t>(state));

        return _putInPacket(packer);
    }

    CustomPacket PacketFactory::createPositionPacket(std::pair<float, float> positionPair, uint64_t entityId)
    {
        BitPacker packer;

        packer.writeUInt16(positionProtocolId);
        packer.writeUInt32(entityId);
        packer.writeFloat(positionPair.first, 0, windowWidth, xPositionFloatPrecision);
        packer.writeFloat(positionPair.second, 0, windowHeight, yPositionFloatPrecision);

        return _putInPacket(packer);
    }

    CustomPacket PacketFactory::createNewEntityPacket(EntityType type, std::pair<float, float> positionPair, uint64_t entityId)
    {
        BitPacker packer;

        packer.writeUInt16(newEntityProtocolId);
        packer.writeUInt32(entityId);
        packer.writeUInt8(static_cast<uint8_t>(type));
        packer.writeFloat(positionPair.first, 0, windowWidth, xPositionFloatPrecision);
        packer.writeFloat(positionPair.second, 0, windowHeight, yPositionFloatPrecision);

        return _putInPacket(packer);
    }

    CustomPacket PacketFactory::createDeleteEntityPacket(uint64_t entityId)
    {
        BitPacker packer;

        packer.writeUInt16(deleteEntityProtocolId);
        packer.writeUInt32(entityId);

        return _putInPacket(packer);
    }

    CustomPacket PacketFactory::createStartGamePacket()
    {
        BitPacker packer;

        packer.writeUInt16(startGameProtocolId);

        return _putInPacket(packer);
    }

    CustomPacket PacketFactory::createLeaveLobbyPacket(uint32_t playerId)
    {
        BitPacker packer;

        packer.writeUInt16(leaveLobbyProtocolId);
        packer.writeUInt32(playerId);

        return _putInPacket(packer);
    }

    CustomPacket PacketFactory::createErrorTcpPacket(uint8_t errorId)
    {
        BitPacker packer;

        packer.writeUInt16(errorTcpProtocolId);
        packer.writeUInt8(errorId);

        return _putInPacket(packer);
    }

    CustomPacket PacketFactory::createJoinLobbyPacket(uint32_t lobbyId, uint8_t lobbyType, uint32_t lobbyCode)

    {
        BitPacker packer;

        packer.writeUInt16(joinLobbyProtocolId);
        packer.writeUInt32(lobbyId);
        packer.writeUInt8(lobbyType);
        packer.writeUInt32(lobbyCode);

        return _putInPacket(packer);
    }

    CustomPacket PacketFactory::createSelectModePacket(uint8_t lobbyType, uint32_t playerId)
    {
        BitPacker packer;

        packer.writeUInt16(selectModeProtocolId);
        packer.writeUInt8(lobbyType);
        packer.writeUInt32(playerId);

        return _putInPacket(packer);
    }

    CustomPacket PacketFactory::createRequestJoinLobbyPacket(uint32_t playerId, uint32_t lobbyCode)
    {
        BitPacker packer;

        packer.writeUInt16(requestJoinLobbyProtocolId);
        packer.writeUInt32(playerId);
        packer.writeUInt32(lobbyCode);

        return _putInPacket(packer);
    }


}// namespace cmn