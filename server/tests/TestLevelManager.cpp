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
        levelManager.loadLevelFromFolder();

        levelManager.setCurrentLevelId(1);
        levelManager.changeToNextLevel();
        ASSERT_EQ(static_cast<int>(levelManager.getCurrentLevel().getLevelId()), 2);
    }

    TEST(ChangeToNextLevelTest, ChangeFail)
    {
        server::LevelManager levelManager;
        server::Level firstLevel;

        levelManager.addLevel(firstLevel);
        levelManager.setCurrentLevelId(1);
        EXPECT_THROW(
            levelManager.changeToNextLevel(),
            std::exception
        );
    }

}
