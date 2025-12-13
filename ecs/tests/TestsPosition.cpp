/*
** EPITECH PROJECT, 2025
** ECSLib
** File description:
** TestsPosition
*/

#include <gtest/gtest.h>

#include "components/Position.hpp"

namespace ecs {
    TEST(EcsManagerTest, GetPosition)
    {
        Position position(60, 50);

        auto firstX = position.getX();
        auto firstY = position.getY();
        auto secondX = 60;
        auto secondY = 50;

        EXPECT_EQ(secondX, firstX);
        EXPECT_EQ(secondY, firstY);
    }

    TEST(EcsManagerTest, SetPosition)
    {
        Position position(30, 50);

        position.setX(25);
        position.setY(0);

        auto firstX = position.getX();
        auto firstY = position.getY();
        auto secondX = 25;
        auto secondY = 0;

        EXPECT_EQ(secondX, firstX);
        EXPECT_EQ(secondY, firstY);
    }
}
