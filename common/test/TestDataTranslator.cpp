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
#include "data_translator/DataTranslator.hpp"
#include "enums/EntityType.hpp"
#include "enums/Key.hpp"
#include "enums/KeyState.hpp"
#include "packet_data/PacketData.hpp"
#include "packet_data/input_packet/InputPacket.hpp"
#include <gtest/gtest.h>

namespace cmn {

    TEST(DataTranslatorTest, InjectInputPacket)
    {
        ecs::EcsManager ecs;
        DataTranslator translator {};

        auto entity = ecs.createEntity(1);
        entity->addComponent<ecs::InputPlayer>();

        inputPacket packet = {
            static_cast<uint8_t>(Keys::Down),
            static_cast<uint8_t>(KeyState::Pressed)
        };
        packetContent const content = packet;
        packetData data = {1, 1, content};

        translator.translate(ecs, data);

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

        auto entity = ecs.createEntity(42);
        entity->addComponent<ecs::Position>(0.F, 0.F);

        positionPacket packet = {100, 200};
        packetContent const content = packet;
        packetData data = {42, 42, content};

        translator.translate(ecs, data);

        auto pos = entity->getComponent<ecs::Position>();
        EXPECT_EQ(pos->getX(), 100.F);
        EXPECT_EQ(pos->getY(), 200.F);
    }

    TEST(DataTranslatorTest, InjectNewEntityPacket)
    {
        ecs::EcsManager ecs;
        DataTranslator translator {};

        newEntityPacket packet = {
            .type=static_cast<uint8_t>(EntityType::Player),
            .posX=10.F,
            .posY=20.F
        };

        packetContent const content = packet;
        packetData data = {7, 5, content};

        translator.translate(ecs, data);

        auto entities = ecs.getEntitiesWithComponent<ecs::Position>();
        ASSERT_EQ(entities.size(), 1);

        const auto& entity = entities.front();
        EXPECT_EQ(entity->getId(), 5);
        EXPECT_TRUE(entity->getComponent<ecs::Sprite>());
        EXPECT_TRUE(entity->getComponent<ecs::Position>());
    }

    TEST(DataTranslatorTest, DeleteEntityPacket)
    {
        ecs::EcsManager ecs;
        DataTranslator translator {};

        auto entity = ecs.createEntity(99);
        entity->addComponent<ecs::Position>(0.F, 0.F);

        deleteEntityPacket packet = {42};
        packetContent const content = packet;
        packetData data = {99, 99, content};

        translator.translate(ecs, data);

        EXPECT_TRUE(entity->getComponent<ecs::Destroy>());
    }

}

