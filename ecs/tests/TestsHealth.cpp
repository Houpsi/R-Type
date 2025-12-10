/*
** EPITECH PROJECT, 2025
** ECSLib
** File description:
** TestsHealth
*/
#include <gtest/gtest.h>

#include "Health.hpp"

TEST(EcsManagerTest, GetHealth) {
    Health health(100);

    auto health1 = health.getHealth();
    auto health2 = 100;

    EXPECT_EQ(health2, health1);
}

TEST(EcsManagerTest, SetHealth) {
    Health health(100);

    health.setHealth(25);
    auto health1 = health.getHealth();
    auto health2 = 25;

    EXPECT_EQ(health2, health1);
}

TEST(EcsManagerTest, SetNegHealth) {
    EXPECT_THROW(
            Health health(-100),
            std::invalid_argument
    );
}

TEST(EcsManagerTest, SetDecimalHealth) {
    EXPECT_THROW(
            Health health(0.5),
            std::invalid_argument
    );
}
