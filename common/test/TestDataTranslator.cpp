/*
** EPITECH PROJECT, 2025
** R_Type
** File description:
** TestDataTranslator
*/

#include "constants/ProtocolConstants.hpp"
#include "EcsManager.hpp"
#include "components/Destroy.hpp"
#include "components/InputPlayer.hpp"
#include "components/Position.hpp"
#include "components/Sprite.hpp"
#include "data_translator/DataTranslator.hpp"
#include "enums/EntityType.hpp"
#include "enums/Key.hpp"
#include "enums/KeyState.hpp"
#include "packet_data/PacketData.hpp"
#include "packet_data/input_data/InputData.hpp"
#include <gtest/gtest.h>

namespace cmn {

    TEST(DataTranslatorTest, InjectInputPacket)
    {
        ecs::EcsManager ecs;
        DataTranslator translator {};
        std::unordered_map<int, uint64_t> playerIdEntityMap;

        auto entity = ecs.createEntity(1);
        entity->addComponent<ecs::InputPlayer>();

        playerIdEntityMap[6] = 1;

        inputData inputData = {
            6,
            static_cast<uint8_t>(Keys::Down),
            static_cast<uint8_t>(KeyState::Pressed)
        };

        packetData data = inputData;

        translator.translate(ecs, data, playerIdEntityMap);

        auto input = entity->getComponent<ecs::InputPlayer>();
        EXPECT_TRUE(input->getDown());
        EXPECT_FALSE(input->getUp());
        EXPECT_FALSE(input->getLeft());
        EXPECT_FALSE(input->getRight());
    }

    TEST(DataTranslatorTest, InjectPositionPacket)
    {
        ecs::EcsManager ecs;
        DataTranslator translator {};
        std::unordered_map<int, uint64_t> playerIdEntityMap;

        auto entity = ecs.createEntity(42);
        entity->addComponent<ecs::Position>(0.F, 0.F);

        positionData positionData = {42, 100, 200};
        packetData data = positionData;

        translator.translate(ecs, data, playerIdEntityMap);

        auto pos = entity->getComponent<ecs::Position>();
        EXPECT_EQ(pos->getX(), 100.F);
        EXPECT_EQ(pos->getY(), 200.F);
    }

    TEST(DataTranslatorTest, InjectNewEntityPacket)
    {
        ecs::EcsManager ecs;
        DataTranslator translator {};
        std::unordered_map<int, uint64_t> playerIdEntityMap;

        newEntityData newEntityData = {
            .entityId=42,
            .type=static_cast<uint8_t>(EntityType::Player),
            .posX=10.F,
            .posY=20.F
        };

        packetData data = newEntityData;

        translator.translate(ecs, data, playerIdEntityMap);

        auto entities = ecs.getEntitiesWithComponent<ecs::Position>();
        ASSERT_EQ(entities.size(), 1);

        const auto& entity = entities.front();
        EXPECT_EQ(entity->getId(), 42);
        EXPECT_TRUE(entity->getComponent<ecs::Sprite>());
        EXPECT_TRUE(entity->getComponent<ecs::Position>());
    }

    TEST(DataTranslatorTest, DeleteEntityPacket)
    {
        ecs::EcsManager ecs;
        DataTranslator translator {};
        std::unordered_map<int, uint64_t> playerIdEntityMap;

        auto entity = ecs.createEntity(42);
        entity->addComponent<ecs::Position>(0.F, 0.F);

        deleteEntityData deleteEntityData = {42};
        packetData data = deleteEntityData;

        translator.translate(ecs, data, playerIdEntityMap);

        EXPECT_TRUE(entity->getComponent<ecs::Destroy>());
    }

}

