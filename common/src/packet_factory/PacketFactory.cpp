/*
** EPITECH PROJECT, 2025
** R_Type
** File description:
** PacketFactory
*/

#include "PacketFactory.hpp"
#include "packet_data/PacketData.hpp"
#include "packet_data/input_packet/InputPacket.hpp"
#include "Constants.hpp"

namespace cmn {

    CustomPacket PacketFactory::createConnectionPacket(uint32_t playerId)
    {
        connectionPacket connection = {playerId};
        packetData const data = {connectionProtocolId, connection};
        CustomPacket packet;
        packet << data;
        return packet;
    }

    CustomPacket PacketFactory::createInputPacket(uint32_t playerId, Keys key, KeyState state)
    {
        inputPacket input = {playerId, static_cast<uint8_t>(key), static_cast<uint8_t>(state)};
        packetData const data = {inputProtocolId, input};
        CustomPacket packet;
        packet << data;
        return packet;
    }

    CustomPacket PacketFactory::createPositionPacket(std::pair<float, float> positionPair, uint64_t entityId)
    {
        positionPacket position = {entityId, positionPair.first, positionPair.second};
        packetData const data = {positionProtocolId, position};
        CustomPacket packet;
        packet << data;
        return packet;
    }

    CustomPacket PacketFactory::createNewEntityPacket(EntityType type, std::pair<float, float> positionPair, uint64_t entityId)
    {
        newEntityPacket newEntity = {entityId, static_cast<uint8_t>(type), positionPair.first, positionPair.second};
        packetData const data = {newEntityProtocolId, newEntity};
        CustomPacket packet;
        packet << data;
        return packet;
    }

    CustomPacket PacketFactory::createDeleteEntityPacket(uint64_t entityId)
    {
        deleteEntityPacket deleteEntity = {entityId};
        packetData const data = {deleteEntityProtocolId, deleteEntity};
        CustomPacket packet;
        packet << data;
        return packet;
    }
    CustomPacket PacketFactory::createStartGamePacket()
    {
        startGamePacket startGame = {};
        packetData const data = {startGameProtocolId, startGame};
        CustomPacket packet;
        packet << data;
        return packet;
    }

}// namespace cmn