/*
** EPITECH PROJECT, 2025
** R_Type
** File description:
** TestPacketFactory
*/

#include <gtest/gtest.h>

#include "packet_factory/PacketFactory.hpp"
#include "custom_packet/CustomPacket.hpp"

#include "packet_data/PacketData.hpp"
#include "packet_data/input_packet/InputPacket.hpp"
#include "packet_data/position_packet/PositionPacket.hpp"
#include "packet_data/new_entity_packet/NewEntityPacket.hpp"
#include "packet_data/delete_entity_packet/DeleteEntityPacket.hpp"

#include "enums/Key.hpp"
#include "enums/KeyState.hpp"
#include "enums/EntityType.hpp"
#include "Constants.hpp"

namespace cmn {

    TEST(PacketFactoryTest, CreateInputPacket)
    {
        CustomPacket packet =
            PacketFactory::createInputPacket(8, Keys::Up, KeyState::Pressed);

        packetData data;
        packet >> data;

        EXPECT_EQ(data.packetId, inputProtocolId);

        inputPacket input{};
        std::visit([&input](auto &&arg) {
            using T = std::decay_t<decltype(arg)>;
            if constexpr (std::is_same_v<T, inputPacket>) {
                input = arg;
            }
        }, data.content);

        EXPECT_EQ(input.playerId, 8);
        EXPECT_EQ(input.key, static_cast<uint8_t>(Keys::Up));
        EXPECT_EQ(input.keyState, static_cast<uint8_t>(KeyState::Pressed));
    }

    TEST(PacketFactoryTest, CreatePositionPacket)
    {
        CustomPacket packet =
            PacketFactory::createPositionPacket({10.F, 20.F}, 42);

        packetData data;
        packet >> data;

        EXPECT_EQ(data.packetId, positionProtocolId);

        positionPacket pos{};
        std::visit([&pos](auto &&arg) {
            using T = std::decay_t<decltype(arg)>;
            if constexpr (std::is_same_v<T, positionPacket>) {
                pos = arg;
            }
        }, data.content);

        EXPECT_FLOAT_EQ(pos.posX, 10.F);
        EXPECT_FLOAT_EQ(pos.posY, 20.F);
        EXPECT_EQ(pos.entityId, 42);
    }

    TEST(PacketFactoryTest, CreateNewEntityPacket)
    {
        CustomPacket packet =
            PacketFactory::createNewEntityPacket(EntityType::Monster, {5.F, 8.F}, 99);

        packetData data;
        packet >> data;

        EXPECT_EQ(data.packetId, newEntityProtocolId);

        newEntityPacket entity{};
        std::visit([&entity](auto &&arg) {
            using T = std::decay_t<decltype(arg)>;
            if constexpr (std::is_same_v<T, newEntityPacket>) {
                entity = arg;
            }
        }, data.content);

        EXPECT_EQ(entity.type, static_cast<uint8_t>(EntityType::Monster));
        EXPECT_FLOAT_EQ(entity.posX, 5.F);
        EXPECT_FLOAT_EQ(entity.posY, 8.F);
        EXPECT_EQ(entity.entityId, 99);
    }

    TEST(PacketFactoryTest, CreateDeleteEntityPacket)
    {
        CustomPacket packet =
            PacketFactory::createDeleteEntityPacket(42);

        packetData data;
        packet >> data;

        EXPECT_EQ(data.packetId, deleteEntityProtocolId);

        deleteEntityPacket del{};
        std::visit([&del](auto &&arg) {
            using T = std::decay_t<decltype(arg)>;
            if constexpr (std::is_same_v<T, deleteEntityPacket>) {
                del = arg;
            }
        }, data.content);

        EXPECT_EQ(del.entityId, 42);
    }

} // namespace cmn
