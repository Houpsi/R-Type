/*
** EPITECH PROJECT, 2025
** R_Type
** File description:
** TestDataTranslator
*/

#include "EcsManager.hpp"
#include "components/Destroy.hpp"
#include "components/InputPlayer.hpp"
#include "components/Position.hpp"
#include "components/Sprite.hpp"
#include "constants/NetworkConstants.hpp"
#include "data_translator/DataTranslator.hpp"
#include "enums/EntityType.hpp"
#include "enums/Key.hpp"
#include "packet_data/InputData.hpp"
#include "packet_data/PacketData.hpp"
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
            Keys::Down,
            true
        };

        packetData data = inputData;

        translator.translate(ecs, data, playerIdEntityMap);

        auto input = entity->getComponent<ecs::InputPlayer>();
        EXPECT_TRUE(input->getDown());
        EXPECT_FALSE(input->getUp());
        EXPECT_FALSE(input->getLeft());
        EXPECT_FALSE(input->getRight());
    }

    TEST(DataTranslatorTest, InjectPositionPacketSingleEntity)
    {
        ecs::EcsManager ecs;
        DataTranslator translator {};
        std::unordered_map<int, uint64_t> playerIdEntityMap;

        auto entity = ecs.createEntity(42);
        entity->addComponent<ecs::Position>(0.F, 0.F);

        positionData positionData = {
            .entityId = {42},
            .posX = {100.0f},
            .posY = {200.0f}
        };

        packetData data = positionData;

        translator.translate(ecs, data, playerIdEntityMap);

        auto pos = entity->getComponent<ecs::Position>();
        EXPECT_EQ(pos->getX(), 100.F);
        EXPECT_EQ(pos->getY(), 200.F);
    }

    TEST(DataTranslatorTest, InjectPositionPacketMultipleEntities)
    {
        ecs::EcsManager ecs;
        DataTranslator translator {};
        std::unordered_map<int, uint64_t> playerIdEntityMap;

        auto entity1 = ecs.createEntity(10);
        entity1->addComponent<ecs::Position>(0.F, 0.F);

        auto entity2 = ecs.createEntity(20);
        entity2->addComponent<ecs::Position>(0.F, 0.F);

        auto entity3 = ecs.createEntity(30);
        entity3->addComponent<ecs::Position>(0.F, 0.F);

        positionData positionData = {
            .entityId = {10, 20, 30},
            .posX = {100.0f, 200.0f, 300.0f},
            .posY = {150.0f, 250.0f, 350.0f}
        };

        packetData data = positionData;

        translator.translate(ecs, data, playerIdEntityMap);

        auto pos1 = entity1->getComponent<ecs::Position>();
        EXPECT_EQ(pos1->getX(), 100.F);
        EXPECT_EQ(pos1->getY(), 150.F);

        auto pos2 = entity2->getComponent<ecs::Position>();
        EXPECT_EQ(pos2->getX(), 200.F);
        EXPECT_EQ(pos2->getY(), 250.F);

        auto pos3 = entity3->getComponent<ecs::Position>();
        EXPECT_EQ(pos3->getX(), 300.F);
        EXPECT_EQ(pos3->getY(), 350.F);
    }

    TEST(DataTranslatorTest, InjectPositionPacketEmptyVectors)
    {
        ecs::EcsManager ecs;
        DataTranslator translator {};
        std::unordered_map<int, uint64_t> playerIdEntityMap;

        positionData positionData = {
            .entityId = {},
            .posX = {},
            .posY = {}
        };

        packetData data = positionData;

        EXPECT_NO_THROW(translator.translate(ecs, data, playerIdEntityMap));
    }

    TEST(DataTranslatorTest, InjectPositionPacketMismatchedSizes)
    {
        ecs::EcsManager ecs;
        DataTranslator translator {};
        std::unordered_map<int, uint64_t> playerIdEntityMap;

        auto entity = ecs.createEntity(42);
        entity->addComponent<ecs::Position>(0.F, 0.F);

        positionData positionData = {
            .entityId = {42, 43},
            .posX = {100.0f},
            .posY = {200.0f}
        };

        packetData data = positionData;

        EXPECT_NO_THROW(translator.translate(ecs, data, playerIdEntityMap));
    }

    TEST(DataTranslatorTest, InjectNewEntityPacket)
    {
        ecs::EcsManager ecs;
        DataTranslator translator {};
        std::unordered_map<int, uint64_t> playerIdEntityMap;

        newEntityData newEntityData = {
            .entityId = 42,
            .type = EntityType::Player,
            .posX = 10.F,
            .posY = 20.F
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

    TEST(DataTranslatorTest, InjectPositionPacketNonExistentEntity)
    {
        ecs::EcsManager ecs;
        DataTranslator translator {};
        std::unordered_map<int, uint64_t> playerIdEntityMap;

        positionData positionData = {
            .entityId = {999},
            .posX = {100.0f},
            .posY = {200.0f}
        };

        packetData data = positionData;

        EXPECT_NO_THROW(translator.translate(ecs, data, playerIdEntityMap));
    }

}