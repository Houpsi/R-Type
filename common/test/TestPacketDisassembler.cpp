/*
** EPITECH PROJECT, 2025
** R_Type
** File description:
** TestPacketDisassembler
*/

#include <gtest/gtest.h>
#include <unordered_map>

#include "constants/NetworkConstants.hpp"
#include "custom_packet/CustomPacket.hpp"
#include "enums/EntityType.hpp"
#include "enums/Key.hpp"
#include "enums/KeyState.hpp"
#include "packet_data/PacketData.hpp"
#include "packet_disassembler/PacketDisassembler.hpp"
#include "packet_factory/PacketFactory.hpp"

namespace cmn {

    class PacketDisassemblerTest : public ::testing::Test {
      protected:
        std::unordered_map<uint32_t, reliablePacket> sequencePacketMap;

        void SetUp() override {
            sequencePacketMap.clear();
        }
    };

    TEST_F(PacketDisassemblerTest, DisassembleConnectionPacket)
    {
        connectionData connData{42};
        CustomPacket packet = PacketFactory::createPacket(connData, sequencePacketMap);
        auto [header, result] = PacketDisassembler::disassemble(packet);

        connectionData data;

        std::visit([&data](auto &&arg) {
            using T = std::decay_t<decltype(arg)>;
            if constexpr (std::is_same_v<T, connectionData>) {
                data = arg;
            }
        }, result);
        EXPECT_EQ(data.playerId, 42);
        EXPECT_EQ(header.protocolId, connectionProtocolId);
        EXPECT_FALSE(header.isReliable);
    }

    TEST_F(PacketDisassemblerTest, DisassembleInputPacket)
    {
        inputData inputDataPacket{10, Keys::Up, KeyState::Pressed};
        CustomPacket packet = PacketFactory::createPacket(inputDataPacket, sequencePacketMap);
        auto [header, result] = PacketDisassembler::disassemble(packet);

        inputData data;

        std::visit([&data](auto &&arg) {
            using T = std::decay_t<decltype(arg)>;
            if constexpr (std::is_same_v<T, inputData>) {
                data = arg;
            }
        }, result);
        EXPECT_EQ(data.playerId, 10);
        EXPECT_EQ(data.key, Keys::Up);
        EXPECT_EQ(data.keyState, KeyState::Pressed);
        EXPECT_EQ(header.protocolId, inputProtocolId);
        EXPECT_FALSE(header.isReliable);
    }

    TEST_F(PacketDisassemblerTest, DisassembleInputPacketAllKeys)
    {
        std::vector<Keys> keys = {
            Keys::Up, Keys::Down, Keys::Left,
            Keys::Right, Keys::Space, Keys::R
        };

        for (auto key : keys) {
            inputData inputDataPacket{5, key, KeyState::Pressed};
            CustomPacket packet = PacketFactory::createPacket(inputDataPacket, sequencePacketMap);
            auto [header, result] = PacketDisassembler::disassemble(packet);

            inputData data;

            std::visit([&data](auto &&arg) {
                using T = std::decay_t<decltype(arg)>;
                if constexpr (std::is_same_v<T, inputData>) {
                    data = arg;
                }
            }, result);
            EXPECT_EQ(data.key, key);
        }
    }

    TEST_F(PacketDisassemblerTest, DisassemblePositionPacket)
    {
        positionData posData{99, 123.45f, 678.90f};
        CustomPacket packet = PacketFactory::createPacket(posData, sequencePacketMap);
        auto [header, result] = PacketDisassembler::disassemble(packet);

        positionData data;
        std::visit([&data](auto &&arg) {
            using T = std::decay_t<decltype(arg)>;
            if constexpr (std::is_same_v<T, positionData>) {
                data = arg;
            }
        }, result);
        EXPECT_EQ(data.entityId, 99);
        EXPECT_NEAR(data.posX, 123.45f, 0.01f);
        EXPECT_NEAR(data.posY, 678.90f, 0.01f);
        EXPECT_EQ(header.protocolId, positionProtocolId);
        EXPECT_FALSE(header.isReliable);
    }

    TEST_F(PacketDisassemblerTest, DisassemblePositionPacketEdgeCases)
    {
        std::vector<std::tuple<uint64_t, float, float>> positions = {
            {1, 0.0f, 0.0f},
            {2, 1920.0f, 1080.0f},
            {3, 960.0f, 540.0f},
            {4, 1.23f, 4.56f}
        };

        for (const auto& [entityId, x, y] : positions) {
            positionData posData{static_cast<uint32_t>(entityId), x, y};
            CustomPacket packet = PacketFactory::createPacket(posData, sequencePacketMap);
            auto [header, result] = PacketDisassembler::disassemble(packet);

            positionData data;

            std::visit([&data](auto &&arg) {
                using T = std::decay_t<decltype(arg)>;
                if constexpr (std::is_same_v<T, positionData>) {
                    data = arg;
                }
            }, result);
            EXPECT_NEAR(data.posX, x, 0.01f);
            EXPECT_NEAR(data.posY, y, 0.01f);
        }
    }

    TEST_F(PacketDisassemblerTest, DisassembleNewEntityPacketPlayer)
    {
        newEntityData newEntData{50, EntityType::Player, 100.0f, 200.0f};
        CustomPacket packet = PacketFactory::createPacket(newEntData, sequencePacketMap);
        auto [header, result] = PacketDisassembler::disassemble(packet);

        newEntityData data;

        std::visit([&data](auto &&arg) {
            using T = std::decay_t<decltype(arg)>;
            if constexpr (std::is_same_v<T, newEntityData>) {
                data = arg;
            }
        }, result);
        EXPECT_EQ(data.entityId, 50);
        EXPECT_EQ(data.type, EntityType::Player);
        EXPECT_NEAR(data.posX, 100.0f, 0.01f);
        EXPECT_NEAR(data.posY, 200.0f, 0.01f);
        EXPECT_EQ(header.protocolId, newEntityProtocolId);
        EXPECT_TRUE(header.isReliable);
    }

    TEST_F(PacketDisassemblerTest, DisassembleNewEntityPacketMonster)
    {
        newEntityData newEntData{75, EntityType::Plane, 500.0f, 600.0f};
        CustomPacket packet = PacketFactory::createPacket(newEntData, sequencePacketMap);
        auto [header, result] = PacketDisassembler::disassemble(packet);

        newEntityData data;

        std::visit([&data](auto &&arg) {
            using T = std::decay_t<decltype(arg)>;
            if constexpr (std::is_same_v<T, newEntityData>) {
                data = arg;
            }
        }, result);
        EXPECT_EQ(data.entityId, 75);
        EXPECT_EQ(data.type, EntityType::Plane);
        EXPECT_NEAR(data.posX, 500.0f, 0.01f);
        EXPECT_NEAR(data.posY, 600.0f, 0.01f);
        EXPECT_EQ(header.protocolId, newEntityProtocolId);
        EXPECT_TRUE(header.isReliable);
    }

    TEST_F(PacketDisassemblerTest, DisassembleNewEntityPacketProjectile)
    {
        newEntityData newEntData{120, EntityType::PlayerProjectile, 800.0f, 900.0f};
        CustomPacket packet = PacketFactory::createPacket(newEntData, sequencePacketMap);
        auto [header, result] = PacketDisassembler::disassemble(packet);

        newEntityData data;

        std::visit([&data](auto &&arg) {
            using T = std::decay_t<decltype(arg)>;
            if constexpr (std::is_same_v<T, newEntityData>) {
                data = arg;
            }
        }, result);
        EXPECT_EQ(data.entityId, 120);
        EXPECT_EQ(data.type, EntityType::PlayerProjectile);
        EXPECT_NEAR(data.posX, 800.0f, 0.01f);
        EXPECT_NEAR(data.posY, 900.0f, 0.01f);
        EXPECT_EQ(header.protocolId, newEntityProtocolId);
        EXPECT_TRUE(header.isReliable);
    }

    TEST_F(PacketDisassemblerTest, DisassembleDeleteEntityPacket)
    {
        deleteEntityData delData{77};
        CustomPacket packet = PacketFactory::createPacket(delData, sequencePacketMap);
        auto [header, result] = PacketDisassembler::disassemble(packet);

        deleteEntityData data;
        std::visit([&data](auto &&arg) {
            using T = std::decay_t<decltype(arg)>;
            if constexpr (std::is_same_v<T, deleteEntityData>) {
                data = arg;
            }
        }, result);
        EXPECT_EQ(data.entityId, 77);
        EXPECT_EQ(header.protocolId, deleteEntityProtocolId);
        EXPECT_TRUE(header.isReliable);
    }

    TEST_F(PacketDisassemblerTest, DisassembleStartGamePacket)
    {
        startGameData startData{};
        CustomPacket packet = PacketFactory::createPacket(startData, sequencePacketMap);
        auto [header, result] = PacketDisassembler::disassemble(packet);

        bool isStartGameData = false;

        std::visit([&isStartGameData](auto &&arg) {
            using T = std::decay_t<decltype(arg)>;
            if constexpr (std::is_same_v<T, startGameData>) {
                isStartGameData = true;
            }
        }, result);
        EXPECT_TRUE(isStartGameData);
        EXPECT_EQ(header.protocolId, startGameProtocolId);
        EXPECT_FALSE(header.isReliable);
    }

    TEST_F(PacketDisassemblerTest, RoundTripConnectionPacket)
    {
        uint32_t originalPlayerId = 123;
        connectionData connData{originalPlayerId};
        CustomPacket packet = PacketFactory::createPacket(connData, sequencePacketMap);
        auto [header, result] = PacketDisassembler::disassemble(packet);

        connectionData data;

        std::visit([&data](auto &&arg) {
            using T = std::decay_t<decltype(arg)>;
            if constexpr (std::is_same_v<T, connectionData>) {
                data = arg;
            }
        }, result);
        EXPECT_EQ(data.playerId, originalPlayerId);
    }

    TEST_F(PacketDisassemblerTest, RoundTripMultiplePackets)
    {
        {
            connectionData connData{10};
            auto packet = PacketFactory::createPacket(connData, sequencePacketMap);
            auto [header, result] = PacketDisassembler::disassemble(packet);
        }

        {
            inputData inputDataPacket{5, Keys::Space, KeyState::Pressed};
            auto packet = PacketFactory::createPacket(inputDataPacket, sequencePacketMap);
            auto [header, result] = PacketDisassembler::disassemble(packet);
        }

        {
            positionData posData{30, 100.0f, 200.0f};
            auto packet = PacketFactory::createPacket(posData, sequencePacketMap);
            auto [header, result] = PacketDisassembler::disassemble(packet);
        }

        {
            newEntityData newEntData{40, EntityType::Plane, 50.0f, 75.0f};
            auto packet = PacketFactory::createPacket(newEntData, sequencePacketMap);
            auto [header, result] = PacketDisassembler::disassemble(packet);
        }

        {
            deleteEntityData delData{50};
            auto packet = PacketFactory::createPacket(delData, sequencePacketMap);
            auto [header, result] = PacketDisassembler::disassemble(packet);
        }

        {
            startGameData startData{};
            auto packet = PacketFactory::createPacket(startData, sequencePacketMap);
            auto [header, result] = PacketDisassembler::disassemble(packet);
        }

        SUCCEED();
    }

    TEST_F(PacketDisassemblerTest, DisassembleMultipleInputStates)
    {
        std::vector<KeyState> states = {KeyState::Pressed, KeyState::Released};

        for (auto state : states) {
            inputData inputDataPacket{7, Keys::Left, state};
            CustomPacket packet = PacketFactory::createPacket(inputDataPacket, sequencePacketMap);
            auto [header, result] = PacketDisassembler::disassemble(packet);

            inputData data;

            std::visit([&data](auto &&arg) {
                using T = std::decay_t<decltype(arg)>;
                if constexpr (std::is_same_v<T, inputData>) {
                    data = arg;
                }
            }, result);
            EXPECT_EQ(data.keyState, state);
        }
    }

    TEST_F(PacketDisassemblerTest, DisassembleWithMaxEntityId)
    {
        uint32_t maxEntityId = UINT32_MAX;

        deleteEntityData delData{maxEntityId};
        CustomPacket packet = PacketFactory::createPacket(delData, sequencePacketMap);
        auto [header, result] = PacketDisassembler::disassemble(packet);

        deleteEntityData data;

        std::visit([&data](auto &&arg) {
            using T = std::decay_t<decltype(arg)>;
            if constexpr (std::is_same_v<T, deleteEntityData>) {
                data = arg;
            }
        }, result);
        EXPECT_EQ(data.entityId, maxEntityId);
    }

    TEST_F(PacketDisassemblerTest, DisassembleSequentialPackets)
    {
        connectionData connData{1};
        inputData inputDataPacket{2, Keys::Up, KeyState::Pressed};
        positionData posData{3, 10.0f, 20.0f};
        newEntityData newEntData{4, EntityType::Player, 30.0f, 40.0f};
        deleteEntityData delData{5};
        startGameData startData{};

        std::vector<CustomPacket> packets = {
            PacketFactory::createPacket(connData, sequencePacketMap),
            PacketFactory::createPacket(inputDataPacket, sequencePacketMap),
            PacketFactory::createPacket(posData, sequencePacketMap),
            PacketFactory::createPacket(newEntData, sequencePacketMap),
            PacketFactory::createPacket(delData, sequencePacketMap),
            PacketFactory::createPacket(startData, sequencePacketMap)
        };

        for (auto& packet : packets) {
            auto [header, result] = PacketDisassembler::disassemble(packet);
        }

        SUCCEED();
    }

    TEST_F(PacketDisassemblerTest, VerifySequencePacketMapPopulation)
    {
        newEntityData newEntData{100, EntityType::Player, 50.0f, 50.0f};
        PacketFactory::createPacket(newEntData, sequencePacketMap);

        deleteEntityData delData{200};
        PacketFactory::createPacket(delData, sequencePacketMap);

        EXPECT_EQ(sequencePacketMap.size(), 2);

        connectionData connData{1};
        PacketFactory::createPacket(connData, sequencePacketMap);

        EXPECT_EQ(sequencePacketMap.size(), 2);
    }

    TEST_F(PacketDisassemblerTest, VerifySequenceNumbers)
    {
        connectionData connData1{1};
        auto packet1 = PacketFactory::createPacket(connData1, sequencePacketMap);
        auto [header1, result1] = PacketDisassembler::disassemble(packet1);

        connectionData connData2{2};
        auto packet2 = PacketFactory::createPacket(connData2, sequencePacketMap);
        auto [header2, result2] = PacketDisassembler::disassemble(packet2);

        EXPECT_EQ(header2.sequenceNbr, header1.sequenceNbr + 1);
    }

    TEST_F(PacketDisassemblerTest, VerifyReliableFlag)
    {
        connectionData connData{1};
        auto unreliablePacket = PacketFactory::createPacket(connData, sequencePacketMap);
        auto [unreliableHeader, unreliableResult] = PacketDisassembler::disassemble(unreliablePacket);
        EXPECT_FALSE(unreliableHeader.isReliable);

        newEntityData newEntData{100, EntityType::Player, 50.0f, 50.0f};
        auto reliablePacket = PacketFactory::createPacket(newEntData, sequencePacketMap);
        auto [reliableHeader, reliableResult] = PacketDisassembler::disassemble(reliablePacket);
        EXPECT_TRUE(reliableHeader.isReliable);
    }

} // namespace cmn