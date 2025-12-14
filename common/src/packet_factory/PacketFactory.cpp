/*
** EPITECH PROJECT, 2025
** R_Type
** File description:
** PacketFactory
*/

#include "PacketFactory.hpp"
#include "packet_data/PacketData.hpp"
#include "packet_data/input_packet/InputPacket.hpp"

namespace cmn {

    constexpr uint16_t inputProtocolId = 0;
    constexpr uint16_t positionProtocolId = 1;
    constexpr uint16_t newEntityProtocolId = 2;
    constexpr uint16_t deleteEntityProtocolId = 3;

    CustomPacket PacketFactory::createInputPacket(Keys key, KeyState state, uint64_t entityId)
    {
        inputPacket input = {static_cast<uint8_t>(key), static_cast<uint8_t>(state)};
        packetData const data = {inputProtocolId, entityId, input};
        CustomPacket packet;
        packet << data;
        return packet;
    }

    CustomPacket PacketFactory::createPositionPacket(std::pair<float, float> positionPair, uint64_t entityId)
    {
        positionPacket position = {positionPair.first, positionPair.second};
        packetData const data = {positionProtocolId, entityId, position};
        CustomPacket packet;
        packet << data;
        return packet;
    }

    CustomPacket PacketFactory::createNewEntityPacket(EntityType type, std::pair<float, float> positionPair, uint64_t entityId)
    {
        newEntityPacket newEntity = {static_cast<uint8_t>(type), positionPair.first, positionPair.second};
        packetData const data = {newEntityProtocolId, entityId, newEntity};
        CustomPacket packet;
        packet << data;
        return packet;
    }

    CustomPacket PacketFactory::createDeleteEntityPacket(uint64_t entityId)
    {
        constexpr uint8_t easter = 42;

        deleteEntityPacket deleteEntity = {easter};
        packetData const data = {deleteEntityProtocolId, entityId, deleteEntity};
        CustomPacket packet;
        packet << data;
        return packet;
    }

}// namespace cmn