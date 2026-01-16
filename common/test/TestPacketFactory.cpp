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
#include "packet_data/input_data/InputData.hpp"
#include "packet_data/position_data/PositionData.hpp"
#include "packet_data/new_entity_data/NewEntityData.hpp"
#include "packet_data/delete_entity_data/DeleteEntityData.hpp"

#include "constants/ProtocolConstants.hpp"
#include "enums/EntityType.hpp"
#include "enums/Key.hpp"
#include "enums/KeyState.hpp"
#include "packet_disassembler/PacketDisassembler.hpp"

namespace cmn {

    TEST(PacketFactoryTest, CreateInputPacket)
    {
        CustomPacket packet = PacketFactory::createInputPacket(8, Keys::Up, KeyState::Pressed);
        auto data = PacketDisassembler::disassemble(packet);
        inputData input{};

        std::visit([&input](auto &&arg) {
            using T = std::decay_t<decltype(arg)>;
            if constexpr (std::is_same_v<T, inputData>) {
                input = arg;
            }
        }, data.value());
        EXPECT_EQ(input.playerId, 8);
        EXPECT_EQ(input.key, static_cast<uint8_t>(Keys::Up));
        EXPECT_EQ(input.keyState, static_cast<uint8_t>(KeyState::Pressed));
    }

    TEST(PacketFactoryTest, CreatePositionPacket)
    {
        CustomPacket packet = PacketFactory::createPositionPacket({10.F, 20.F}, 42);
        auto data = PacketDisassembler::disassemble(packet);
        positionData pos{};

        std::visit([&pos](auto &&arg) {
            using T = std::decay_t<decltype(arg)>;
            if constexpr (std::is_same_v<T, positionData>) {
                pos = arg;
            }
        }, data.value());
        EXPECT_FLOAT_EQ(pos.posX, 10.F);
        EXPECT_FLOAT_EQ(pos.posY, 20.F);
        EXPECT_EQ(pos.entityId, 42);
    }

    TEST(PacketFactoryTest, CreateNewEntityPacket)
    {
        CustomPacket packet = PacketFactory::createNewEntityPacket(EntityType::Plane, {5.F, 8.F}, 99);
        auto data = PacketDisassembler::disassemble(packet);
        newEntityData entity{};

        std::visit([&entity](auto &&arg) {
            using T = std::decay_t<decltype(arg)>;
            if constexpr (std::is_same_v<T, newEntityData>) {
                entity = arg;
            }
        }, data.value());
        EXPECT_EQ(entity.type, static_cast<uint8_t>(EntityType::Plane));
        EXPECT_FLOAT_EQ(entity.posX, 5.F);
        EXPECT_FLOAT_EQ(entity.posY, 8.F);
        EXPECT_EQ(entity.entityId, 99);
    }

    TEST(PacketFactoryTest, CreateDeleteEntityPacket)
    {
        CustomPacket packet = PacketFactory::createDeleteEntityPacket(42);
        auto data = PacketDisassembler::disassemble(packet);
        deleteEntityData del{};

        std::visit([&del](auto &&arg) {
            using T = std::decay_t<decltype(arg)>;
            if constexpr (std::is_same_v<T, deleteEntityData>) {
                del = arg;
            }
        }, data.value());
        EXPECT_EQ(del.entityId, 42);
    }

} // namespace cmn
