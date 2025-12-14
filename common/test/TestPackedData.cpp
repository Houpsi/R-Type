/*
** EPITECH PROJECT, 2025
** R_Type
** File description:
** TestPackedData
*/
#include "custom_packet/CustomPacket.hpp"
#include "enums/Key.hpp"
#include "enums/KeyState.hpp"
#include "packet_data/PacketData.hpp"
#include "packet_data/input_packet/InputPacket.hpp"
#include <gtest//gtest.h>
#include <string>

namespace cmn {

    TEST(InputPacketTest, OperatorOverload)
    {
        CustomPacket customPacket;
        const inputPacket packet = {6, static_cast<uint8_t>(Keys::Up), static_cast<uint8_t>(KeyState::Pressed)};
        customPacket << packet;
        inputPacket tmp;
        customPacket >> tmp;
        EXPECT_EQ(tmp.playerId, 6);
        EXPECT_EQ(tmp.key, static_cast<uint8_t>(Keys::Up));
        EXPECT_EQ(tmp.keyState, static_cast<uint8_t>(KeyState::Pressed));
    }

    TEST(PacketContentTest, OperatorOverload)
    {
        CustomPacket customPacket;
        const inputPacket packet = {6, static_cast<uint8_t>(Keys::Up), static_cast<uint8_t>(KeyState::Pressed)};
        packetContent const content = packet;
        customPacket << content;
        packetContent tmp;
        customPacket >> tmp;
        inputPacket inputTmp;
        std::visit([&inputTmp](auto &&arg) {
            using T = std::decay_t<decltype(arg)>;
            if constexpr (std::is_same_v<T, inputPacket>) {
                inputTmp = arg;
            }
        }, tmp);
        EXPECT_EQ(inputTmp.playerId, 6);
        EXPECT_EQ(inputTmp.key, static_cast<uint8_t>(Keys::Up));
        EXPECT_EQ(inputTmp.keyState, static_cast<uint8_t>(KeyState::Pressed));
    }

    TEST(PacketDataTest, OperatorOverload)
    {
        CustomPacket customPacket;
        const inputPacket packet = {6, static_cast<uint8_t>(Keys::Up), static_cast<uint8_t>(KeyState::Pressed)};
        packetContent const content = packet;
        packetData const data = {1, content};
        customPacket << data;
        packetData tmpData;
        customPacket >> tmpData;
        inputPacket inputTmp;
        std::visit([&inputTmp](auto &&arg) {
            using T = std::decay_t<decltype(arg)>;
            if constexpr (std::is_same_v<T, inputPacket>) {
                inputTmp = arg;
            }
        }, tmpData.content);
        EXPECT_EQ(inputTmp.playerId, 6);
        EXPECT_EQ(inputTmp.key, static_cast<uint8_t>(Keys::Up));
        EXPECT_EQ(inputTmp.keyState, static_cast<uint8_t>(KeyState::Pressed));
        EXPECT_EQ(tmpData.packetId, 1);
    }

}
