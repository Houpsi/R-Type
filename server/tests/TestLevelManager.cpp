/*
** EPITECH PROJECT, 2025
** R_Type
** File description:
** TestLevelManager
*/

#include "level/Level.hpp"
#include "level_manager/LevelManager.hpp"
#include <gtest//gtest.h>

namespace test {

    TEST(ChangeToNextlevelTest, SuccessfulChange)
    {
        server::LevelManager levelManager;
        server::Level firstLevel(1, 10, false, 0);
        server::Level secondLevel(2, 20, true, 300);

        levelManager.addLevel(firstLevel);
        levelManager.addLevel(secondLevel);
        levelManager.setCurrentLevelId(1);
        levelManager.changeToNextLevel();
        ASSERT_EQ(levelManager.getCurrentLevel().getLevelId(), 2);
    }

    TEST(ChangeToNextLevelTest, ChangeFail)
    {
        server::LevelManager levelManager;
        server::Level firstLevel(1, 10, false, 0);

        levelManager.addLevel(firstLevel);
        levelManager.setCurrentLevelId(1);
        EXPECT_THROW(
            levelManager.changeToNextLevel(),
            std::exception
        );
    }

}
