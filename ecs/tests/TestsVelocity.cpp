/*
** EPITECH PROJECT, 2025
** r-type_client
** File description:
** TestsVelocity
*/

#include <gtest/gtest.h>
#include "components/Velocity.hpp"

namespace ecs
{
    TEST(VelocityTest, ConstructorAssignsCorrectValues) {
        Velocity v(10.f, 90);

        EXPECT_FLOAT_EQ(v.getVelocity(), 10.f);
        EXPECT_EQ(v.getDirection(), 90);
    }

    TEST(VelocityTest, ConstructorAcceptsNegativeVelocity) {
        Velocity v(-5.f, 0);

        EXPECT_FLOAT_EQ(v.getVelocity(), -5.f);
        EXPECT_EQ(v.getDirection(), 0);
    }

    TEST(VelocityTest, ConstructorAcceptsExtremeDirection) {
        Velocity v(3.f, 999999);

        EXPECT_FLOAT_EQ(v.getVelocity(), 3.f);
        EXPECT_EQ(v.getDirection(), 999999);
    }

    TEST(VelocityTest, SetVelocityWorks) {
        Velocity v(0.f, 0);

        v.setVelocity(42.f);
        EXPECT_FLOAT_EQ(v.getVelocity(), 42.f);

        v.setVelocity(-12.5f);
        EXPECT_FLOAT_EQ(v.getVelocity(), -12.5f);

        v.setVelocity(0.f);
        EXPECT_FLOAT_EQ(v.getVelocity(), 0.f);
    }

    TEST(VelocityTest, SetDirectionWorks) {
        Velocity v(10.f, 0);

        v.setDirection(180);
        EXPECT_EQ(v.getDirection(), 180);

        v.setDirection(-90);
        EXPECT_EQ(v.getDirection(), -90);

        v.setDirection(9999);
        EXPECT_EQ(v.getDirection(), 9999);
    }

    TEST(VelocityTest, ZeroVelocityEdgeCase) {
        Velocity v(0.f, 45);

        EXPECT_FLOAT_EQ(v.getVelocity(), 0.f);
        EXPECT_EQ(v.getDirection(), 45);

        v.setVelocity(0.f);
        EXPECT_FLOAT_EQ(v.getVelocity(), 0.f);
    }

    TEST(VelocityTest, NegativeDirectionEdgeCase) {
        Velocity v(5.f, -360);

        EXPECT_EQ(v.getDirection(), -360);

        v.setDirection(-1);
        EXPECT_EQ(v.getDirection(), -1);
    }

    TEST(VelocityTest, ExtremeFloatVelocity) {
        Velocity v(1e38f, 45);

        EXPECT_FLOAT_EQ(v.getVelocity(), 1e38f);

        v.setVelocity(-1e38f);
        EXPECT_FLOAT_EQ(v.getVelocity(), -1e38f);
    }

    TEST(VelocityTest, MultipleChangesSequence) {
        Velocity v(1.f, 0);

        for (int i = 0; i < 1000; i++) {
            v.setVelocity(v.getVelocity() + 0.5f);
            v.setDirection(v.getDirection() + 1);

            EXPECT_FLOAT_EQ(v.getVelocity(), 1.f + 0.5f * (i + 1));
            EXPECT_EQ(v.getDirection(), (i + 1));
        }
    }
}