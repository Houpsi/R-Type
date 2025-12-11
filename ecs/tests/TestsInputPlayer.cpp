/*
** EPITECH PROJECT, 2025
** ECSLib
** File description:
** TestsInputPlayer
*/
#include <gtest/gtest.h>

#include "components/InputPlayer.hpp"

namespace ecs {
    TEST(InputPlayerTest, SetValueToLeft)
    {
        InputPlayer inputPlayer;

        inputPlayer.setLeft(true);

        EXPECT_EQ(true, inputPlayer.getLeft());
    }

    TEST(InputPlayerTest, SetValueToRight)
    {
        InputPlayer inputPlayer;

        inputPlayer.setRight(true);

        EXPECT_EQ(true, inputPlayer.getRight());
    }

    TEST(InputPlayerTest, SetValueToUp)
    {
        InputPlayer inputPlayer;

        inputPlayer.setUp(true);

        EXPECT_EQ(true, inputPlayer.getUp());
    }

    TEST(InputPlayerTest, SetValueToDown)
    {
        InputPlayer inputPlayer;

        inputPlayer.setDown(true);

        EXPECT_EQ(true, inputPlayer.getDown());
    }
}
