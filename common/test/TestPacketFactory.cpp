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
#include "packet_data/StartGameData.hpp"

#include "enums/EntityType.hpp"
#include "enums/Key.hpp"
#include "enums/KeyState.hpp"
#include "packet_disassembler/PacketDisassembler.hpp"

namespace cmn {

    class PacketFactoryTest : public ::testing::Test {
      protected:
        std::unordered_map<uint32_t, CustomPacket> sequencePacketMap;

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
        inputData inputDataPacket{8, Keys::Up, KeyState::Pressed};
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
        EXPECT_EQ(input.keyState, KeyState::Pressed);
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
        newEntityData newEntData{99, EntityType::Monster, 5.F, 8.F};
        CustomPacket packet = PacketFactory::createPacket(newEntData, sequencePacketMap);
        auto [header, data] = PacketDisassembler::disassemble(packet);
        newEntityData entity{};

        std::visit([&entity](auto &&arg) {
            using T = std::decay_t<decltype(arg)>;
            if constexpr (std::is_same_v<T, newEntityData>) {
                entity = arg;
            }
        }, data);
        EXPECT_EQ(entity.type, EntityType::Monster);
        EXPECT_FLOAT_EQ(entity.posX, 5.F);
        EXPECT_FLOAT_EQ(entity.posY, 8.F);
        EXPECT_EQ(entity.entityId, 99);
        EXPECT_TRUE(header.isReliable);

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
        EXPECT_TRUE(header.isReliable);

        EXPECT_EQ(sequencePacketMap.size(), 1);
    }

    TEST_F(PacketFactoryTest, CreateStartGamePacket)
    {
        startGameData startData{};
        CustomPacket packet = PacketFactory::createPacket(startData, sequencePacketMap);
        auto [header, data] = PacketDisassembler::disassemble(packet);

        bool isStartGameData = false;
        std::visit([&isStartGameData](auto &&arg) {
            using T = std::decay_t<decltype(arg)>;
            if constexpr (std::is_same_v<T, startGameData>) {
                isStartGameData = true;
            }
        }, data);
        EXPECT_TRUE(isStartGameData);
        EXPECT_FALSE(header.isReliable);
    }

    TEST_F(PacketFactoryTest, VerifySequenceNumberIncrement)
    {
        connectionData connData1{1};
        auto packet1 = PacketFactory::createPacket(connData1, sequencePacketMap);
        auto [header1, data1] = PacketDisassembler::disassemble(packet1);

        connectionData connData2{2};
        auto packet2 = PacketFactory::createPacket(connData2, sequencePacketMap);
        auto [header2, data2] = PacketDisassembler::disassemble(packet2);

        connectionData connData3{3};
        auto packet3 = PacketFactory::createPacket(connData3, sequencePacketMap);
        auto [header3, data3] = PacketDisassembler::disassemble(packet3);

        EXPECT_EQ(header2.sequenceNbr, header1.sequenceNbr + 1);
        EXPECT_EQ(header3.sequenceNbr, header2.sequenceNbr + 1);
    }

    TEST_F(PacketFactoryTest, VerifyReliablePacketsStoredInMap)
    {
        connectionData connData{1};
        PacketFactory::createPacket(connData, sequencePacketMap);
        EXPECT_EQ(sequencePacketMap.size(), 0);

        inputData inputDataPacket{2, Keys::Up, KeyState::Pressed};
        PacketFactory::createPacket(inputDataPacket, sequencePacketMap);
        EXPECT_EQ(sequencePacketMap.size(), 0);

        newEntityData newEntData{100, EntityType::Player, 50.0f, 50.0f};
        PacketFactory::createPacket(newEntData, sequencePacketMap);
        EXPECT_EQ(sequencePacketMap.size(), 1);

        deleteEntityData delData{200};
        PacketFactory::createPacket(delData, sequencePacketMap);
        EXPECT_EQ(sequencePacketMap.size(), 2);
    }

    TEST_F(PacketFactoryTest, MultiplePacketsRoundTrip)
    {
        std::vector<packetData> originalData = {
            connectionData{10},
            inputData{20, Keys::Space, KeyState::Pressed},
            positionData{30, 100.5f, 200.7f},
            newEntityData{40, EntityType::Monster, 50.0f, 75.0f},
            deleteEntityData{50},
            startGameData{}
        };

        for (const auto& original : originalData) {
            auto packet = PacketFactory::createPacket(original, sequencePacketMap);
            auto [header, disassembled] = PacketDisassembler::disassemble(packet);

            EXPECT_EQ(original.index(), disassembled.index());
        }
    }

} // namespace cmn