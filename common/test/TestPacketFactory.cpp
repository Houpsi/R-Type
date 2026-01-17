/*
** EPITECH PROJECT, 2025
** R_Type
** File description:
** TestPacketFactory
*/

#include <gtest/gtest.h>
#include <unordered_map>

#include "packet_factory/PacketFactory.hpp"
#include "custom_packet/CustomPacket.hpp"

#include "packet_data/DeleteEntityData.hpp"
#include "packet_data/InputData.hpp"
#include "packet_data/NewEntityData.hpp"
#include "packet_data/PacketData.hpp"
#include "packet_data/PositionData.hpp"
#include "packet_data/ConnectionData.hpp"

#include "enums/EntityType.hpp"
#include "enums/Key.hpp"
#include "packet_disassembler/PacketDisassembler.hpp"

namespace cmn {

    class PacketFactoryTest : public ::testing::Test {
      protected:
        std::unordered_map<uint32_t, reliablePacket> sequencePacketMap;

        void SetUp() override {
            sequencePacketMap.clear();
        }
    };

    TEST_F(PacketFactoryTest, CreateConnectionPacket)
    {
        connectionData connData{42};
        CustomPacket packet = PacketFactory::createPacket(connData, sequencePacketMap);
        auto [header, data] = PacketDisassembler::disassemble(packet);
        connectionData conn{};

        std::visit([&conn](auto &&arg) {
            using T = std::decay_t<decltype(arg)>;
            if constexpr (std::is_same_v<T, connectionData>) {
                conn = arg;
            }
        }, data);
        EXPECT_EQ(conn.playerId, 42);
        EXPECT_FALSE(header.isReliable);
    }

    TEST_F(PacketFactoryTest, CreateInputPacket)
    {
        inputData inputDataPacket{8, Keys::Up, true};
        CustomPacket packet = PacketFactory::createPacket(inputDataPacket, sequencePacketMap);
        auto [header, data] = PacketDisassembler::disassemble(packet);
        inputData input{};

        std::visit([&input](auto &&arg) {
            using T = std::decay_t<decltype(arg)>;
            if constexpr (std::is_same_v<T, inputData>) {
                input = arg;
            }
        }, data);
        EXPECT_EQ(input.playerId, 8);
        EXPECT_EQ(input.key, Keys::Up);
        EXPECT_EQ(input.pressed, true);
        EXPECT_FALSE(header.isReliable);
    }

    TEST_F(PacketFactoryTest, CreatePositionPacket)
    {
        positionData posData{42, 10.F, 20.F};
        CustomPacket packet = PacketFactory::createPacket(posData, sequencePacketMap);
        auto [header, data] = PacketDisassembler::disassemble(packet);
        positionData pos{};

        std::visit([&pos](auto &&arg) {
            using T = std::decay_t<decltype(arg)>;
            if constexpr (std::is_same_v<T, positionData>) {
                pos = arg;
            }
        }, data);
        EXPECT_FLOAT_EQ(pos.posX, 10.F);
        EXPECT_FLOAT_EQ(pos.posY, 20.F);
        EXPECT_EQ(pos.entityId, 42);
        EXPECT_FALSE(header.isReliable);
    }

    TEST_F(PacketFactoryTest, CreateNewEntityPacket)
    {
        newEntityData entity = {99, EntityType::Plane, 5.0F, 8.0F};
        CustomPacket packet = PacketFactory::createPacket(entity, sequencePacketMap);
        auto data = PacketDisassembler::disassemble(packet);

        std::visit([&entity](auto &&arg) {
            using T = std::decay_t<decltype(arg)>;
            if constexpr (std::is_same_v<T, newEntityData>) {
                 entity = arg;
            }
        }, data.second);
        EXPECT_EQ(entity.type, EntityType::Plane);
        EXPECT_FLOAT_EQ(entity.posX, 5.F);
        EXPECT_FLOAT_EQ(entity.posY, 8.F);
        EXPECT_EQ(entity.entityId, 99);

        EXPECT_EQ(sequencePacketMap.size(), 1);
    }

    TEST_F(PacketFactoryTest, CreateDeleteEntityPacket)
    {
        deleteEntityData delData{42};
        CustomPacket packet = PacketFactory::createPacket(delData, sequencePacketMap);
        auto [header, data] = PacketDisassembler::disassemble(packet);
        deleteEntityData del{};

        std::visit([&del](auto &&arg) {
            using T = std::decay_t<decltype(arg)>;
            if constexpr (std::is_same_v<T, deleteEntityData>) {
                del = arg;
            }
        }, data);
        EXPECT_EQ(del.entityId, 42);
    }

} // namespace cmn