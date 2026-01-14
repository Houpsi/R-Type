/*
** EPITECH PROJECT, 2025
** R_Type
** File description:
** TestPacketDisassembler
*/

#include <gtest/gtest.h>

#include "packet_disassembler/PacketDisassembler.hpp"
#include "packet_factory/PacketFactory.hpp"
#include "custom_packet/CustomPacket.hpp"
#include "packet_data/PacketData.hpp"
#include "enums/EntityType.hpp"
#include "enums/Key.hpp"
#include "enums/KeyState.hpp"

namespace cmn {

    TEST(PacketDisassemblerTest, DisassembleConnectionPacket)
    {
        CustomPacket packet = PacketFactory::createConnectionPacket(42);
        auto result = PacketDisassembler::disassemble(packet);

        ASSERT_TRUE(result.has_value());

        connectionData data;

        std::visit([&data](auto &&arg) {
            using T = std::decay_t<decltype(arg)>;
            if constexpr (std::is_same_v<T, connectionData>) {
                data = arg;
            }
        }, result.value());
        EXPECT_EQ(data.playerId, 42);
    }

    TEST(PacketDisassemblerTest, DisassembleInputPacket)
    {
        CustomPacket packet = PacketFactory::createInputPacket(
            10,
            Keys::Up,
            KeyState::Pressed
        );
        auto result = PacketDisassembler::disassemble(packet);

        ASSERT_TRUE(result.has_value());

        inputData data;

        std::visit([&data](auto &&arg) {
            using T = std::decay_t<decltype(arg)>;
            if constexpr (std::is_same_v<T, inputData>) {
                data = arg;
            }
        }, result.value());
        EXPECT_EQ(data.playerId, 10);
        EXPECT_EQ(data.key, static_cast<uint8_t>(Keys::Up));
        EXPECT_EQ(data.keyState, static_cast<uint8_t>(KeyState::Pressed));
    }

    TEST(PacketDisassemblerTest, DisassembleInputPacketAllKeys)
    {
        std::vector<Keys> keys = {
            Keys::Up, Keys::Down, Keys::Left,
            Keys::Right, Keys::Space, Keys::R
        };

        for (auto key : keys) {
            CustomPacket packet = PacketFactory::createInputPacket(5, key, KeyState::Pressed);
            auto result = PacketDisassembler::disassemble(packet);

            ASSERT_TRUE(result.has_value());

            inputData data;

            std::visit([&data](auto &&arg) {
                using T = std::decay_t<decltype(arg)>;
                if constexpr (std::is_same_v<T, inputData>) {
                    data = arg;
                }
            }, result.value());
            EXPECT_EQ(data.key, static_cast<uint8_t>(key));
        }
    }

    TEST(PacketDisassemblerTest, DisassemblePositionPacket)
    {
        CustomPacket packet = PacketFactory::createPositionPacket(
            {123.45f, 678.90f},
            99
        );
        auto result = PacketDisassembler::disassemble(packet);

        ASSERT_TRUE(result.has_value());

        positionData data;
        std::visit([&data](auto &&arg) {
            using T = std::decay_t<decltype(arg)>;
            if constexpr (std::is_same_v<T, positionData>) {
                data = arg;
            }
        }, result.value());
        EXPECT_EQ(data.entityId, 99);
        EXPECT_NEAR(data.posX, 123.45f, 0.01f);
        EXPECT_NEAR(data.posY, 678.90f, 0.01f);
    }

    TEST(PacketDisassemblerTest, DisassemblePositionPacketEdgeCases)
    {
        std::vector<std::pair<float, float>> positions = {
            {0.0f, 0.0f},
            {1920.0f, 1080.0f},
            {960.0f, 540.0f},
            {1.23f, 4.56f}
        };

        for (const auto& pos : positions) {
            CustomPacket packet = PacketFactory::createPositionPacket(pos, 1);
            auto result = PacketDisassembler::disassemble(packet);

            ASSERT_TRUE(result.has_value());

            positionData data;

            std::visit([&data](auto &&arg) {
                using T = std::decay_t<decltype(arg)>;
                if constexpr (std::is_same_v<T, positionData>) {
                    data = arg;
                }
            }, result.value());
            EXPECT_NEAR(data.posX, pos.first, 0.01f);
            EXPECT_NEAR(data.posY, pos.second, 0.01f);
        }
    }

    TEST(PacketDisassemblerTest, DisassembleNewEntityPacketPlayer)
    {
        CustomPacket packet = PacketFactory::createNewEntityPacket(
            EntityType::Player,
            {100.0f, 200.0f},
            50
        );
        auto result = PacketDisassembler::disassemble(packet);

        ASSERT_TRUE(result.has_value());

        newEntityData data;

        std::visit([&data](auto &&arg) {
            using T = std::decay_t<decltype(arg)>;
            if constexpr (std::is_same_v<T, newEntityData>) {
                data = arg;
            }
        }, result.value());
        EXPECT_EQ(data.entityId, 50);
        EXPECT_EQ(data.type, static_cast<uint8_t>(EntityType::Player));
        EXPECT_NEAR(data.posX, 100.0f, 0.01f);
        EXPECT_NEAR(data.posY, 200.0f, 0.01f);
    }

    TEST(PacketDisassemblerTest, DisassembleNewEntityPacketMonster)
    {
        CustomPacket packet = PacketFactory::createNewEntityPacket(
            EntityType::Monster,
            {500.0f, 600.0f},
            75
        );
        auto result = PacketDisassembler::disassemble(packet);

        ASSERT_TRUE(result.has_value());

        newEntityData data;

        std::visit([&data](auto &&arg) {
            using T = std::decay_t<decltype(arg)>;
            if constexpr (std::is_same_v<T, newEntityData>) {
                data = arg;
            }
        }, result.value());
        EXPECT_EQ(data.entityId, 75);
        EXPECT_EQ(data.type, static_cast<uint8_t>(EntityType::Monster));
        EXPECT_NEAR(data.posX, 500.0f, 0.01f);
        EXPECT_NEAR(data.posY, 600.0f, 0.01f);
    }

    TEST(PacketDisassemblerTest, DisassembleNewEntityPacketProjectile)
    {
        CustomPacket packet = PacketFactory::createNewEntityPacket(
            EntityType::PlayerProjectile,
            {800.0f, 900.0f},
            120
        );
        auto result = PacketDisassembler::disassemble(packet);

        ASSERT_TRUE(result.has_value());

        newEntityData data;

        std::visit([&data](auto &&arg) {
            using T = std::decay_t<decltype(arg)>;
            if constexpr (std::is_same_v<T, newEntityData>) {
                data = arg;
            }
        }, result.value());
        EXPECT_EQ(data.entityId, 120);
        EXPECT_EQ(data.type, static_cast<uint8_t>(EntityType::PlayerProjectile));
        EXPECT_NEAR(data.posX, 800.0f, 0.01f);
        EXPECT_NEAR(data.posY, 900.0f, 0.01f);
    }

    TEST(PacketDisassemblerTest, DisassembleDeleteEntityPacket)
    {
        CustomPacket packet = PacketFactory::createDeleteEntityPacket(77);
        auto result = PacketDisassembler::disassemble(packet);

        ASSERT_TRUE(result.has_value());

        deleteEntityData data;
        std::visit([&data](auto &&arg) {
            using T = std::decay_t<decltype(arg)>;
            if constexpr (std::is_same_v<T, deleteEntityData>) {
                data = arg;
            }
        }, result.value());
        EXPECT_EQ(data.entityId, 77);
    }

    TEST(PacketDisassemblerTest, DisassembleStartGamePacket)
    {
        CustomPacket packet = PacketFactory::createStartGamePacket();
        auto result = PacketDisassembler::disassemble(packet);

        ASSERT_TRUE(result.has_value());

        bool isStartGameData = false;

        std::visit([&isStartGameData](auto &&arg) {
            using T = std::decay_t<decltype(arg)>;
            if constexpr (std::is_same_v<T, startGameData>) {
                isStartGameData = true;
            }
        }, result.value());
        EXPECT_TRUE(isStartGameData);
    }

    TEST(PacketDisassemblerTest, RoundTripConnectionPacket)
    {
        uint32_t originalPlayerId = 123;
        CustomPacket packet = PacketFactory::createConnectionPacket(originalPlayerId);
        auto result = PacketDisassembler::disassemble(packet);

        ASSERT_TRUE(result.has_value());

        connectionData data;

        std::visit([&data](auto &&arg) {
            using T = std::decay_t<decltype(arg)>;
            if constexpr (std::is_same_v<T, connectionData>) {
                data = arg;
            }
        }, result.value());
        EXPECT_EQ(data.playerId, originalPlayerId);
    }

    TEST(PacketDisassemblerTest, RoundTripMultiplePackets)
    {
        {
            auto packet = PacketFactory::createConnectionPacket(10);
            auto result = PacketDisassembler::disassemble(packet);
            EXPECT_TRUE(result.has_value());
        }

        {
            auto packet = PacketFactory::createInputPacket(5, Keys::Space, KeyState::Pressed);
            auto result = PacketDisassembler::disassemble(packet);
            EXPECT_TRUE(result.has_value());
        }

        {
            auto packet = PacketFactory::createPositionPacket({100.0f, 200.0f}, 30);
            auto result = PacketDisassembler::disassemble(packet);
            EXPECT_TRUE(result.has_value());
        }

        {
            auto packet = PacketFactory::createNewEntityPacket(EntityType::Monster, {50.0f, 75.0f}, 40);
            auto result = PacketDisassembler::disassemble(packet);
            EXPECT_TRUE(result.has_value());
        }

        {
            auto packet = PacketFactory::createDeleteEntityPacket(50);
            auto result = PacketDisassembler::disassemble(packet);
            EXPECT_TRUE(result.has_value());
        }

        {
            auto packet = PacketFactory::createStartGamePacket();
            auto result = PacketDisassembler::disassemble(packet);
            EXPECT_TRUE(result.has_value());
        }
    }

    TEST(PacketDisassemblerTest, DisassembleMultipleInputStates)
    {
        std::vector<KeyState> states = {KeyState::Pressed, KeyState::Released};

        for (auto state : states) {
            CustomPacket packet = PacketFactory::createInputPacket(7, Keys::Left, state);
            auto result = PacketDisassembler::disassemble(packet);

            ASSERT_TRUE(result.has_value());

            inputData data;

            std::visit([&data](auto &&arg) {
                using T = std::decay_t<decltype(arg)>;
                if constexpr (std::is_same_v<T, inputData>) {
                    data = arg;
                }
            }, result.value());
            EXPECT_EQ(data.keyState, static_cast<uint8_t>(state));
        }
    }

    TEST(PacketDisassemblerTest, DisassembleWithMaxEntityId)
    {
        uint32_t maxEntityId = 4294967295;

        CustomPacket packet = PacketFactory::createDeleteEntityPacket(maxEntityId);
        auto result = PacketDisassembler::disassemble(packet);

        ASSERT_TRUE(result.has_value());

        deleteEntityData data;

        std::visit([&data](auto &&arg) {
            using T = std::decay_t<decltype(arg)>;
            if constexpr (std::is_same_v<T, deleteEntityData>) {
                data = arg;
            }
        }, result.value());
        EXPECT_EQ(data.entityId, maxEntityId);
    }

    TEST(PacketDisassemblerTest, DisassembleSequentialPackets)
    {
        std::vector<CustomPacket> packets = {
            PacketFactory::createConnectionPacket(1),
            PacketFactory::createInputPacket(2, Keys::Up, KeyState::Pressed),
            PacketFactory::createPositionPacket({10.0f, 20.0f}, 3),
            PacketFactory::createNewEntityPacket(EntityType::Player, {30.0f, 40.0f}, 4),
            PacketFactory::createDeleteEntityPacket(5),
            PacketFactory::createStartGamePacket()
        };

        for (auto& packet : packets) {
            auto result = PacketDisassembler::disassemble(packet);
            EXPECT_TRUE(result.has_value());
        }
    }

} // namespace cmn