/*
** EPITECH PROJECT, 2026
** R_Type
** File description:
** TestLevelParser
*/
#include <gtest/gtest.h>
#include "parser/LevelParser.hpp"

TEST(LevelParser, ValidLevelIsParsedCorrectly)
{
    server::LevelParser parser;
    server::Level level;
    parser.createLevel("L", level);

    EXPECT_EQ(level.getLevelId(), 1);
    EXPECT_EQ(level.getNameLevel(), "Level 1");
    EXPECT_EQ(level.getPlayerSpeed(), 200);
    EXPECT_TRUE(level.getIsBossPresent());

}

TEST(LevelParser, InvalidIdReturnsDefaultLevel)
{
    server::LevelParser parser;
    server::Level level;
    parser.createLevel("LevelsForLevelParser/invalid_id.cfg",level);

    EXPECT_NE(level.getLevelId(), 999);
}

TEST(LevelParser, UnknownEnemyTypeFailsParsing)
{
    server::LevelParser parser;
    server::Level level;
    parser.createLevel("LevelsForLevelParser/invalid_test.cfg", level);

    EXPECT_EQ(level.getWaves().size(), 0);
}

TEST(LevelParser, LevelWithoutBoss)
{
    server::LevelParser parser;
    server::Level level;
    parser.createLevel("LevelsForLevelParser/no_boss.cfg", level);

    EXPECT_FALSE(level.getIsBossPresent());
}

TEST(LevelParser, InvalidScrollSpeed)
{
    server::LevelParser parser;
    server::Level level;
    parser.createLevel("LevelsForLevelParser/invalid-speed.cfg", level);

    EXPECT_EQ(level.getPlayerSpeed(), cmn::playerSpeed);
}
