/*
** EPITECH PROJECT, 2025
** test
** File description:
** test
*/
#include <gtest//gtest.h>
#include <parser/Parser.hpp>
#include <string>

namespace test {

    /* Argument parsing tests */

    TEST(ArgumentParsingTest, HandleTooManyArguments)
    {
        server::Parser parser{};
        std::array argv = {"hello", "world", "test"};
        EXPECT_FALSE(parser.isEveryArgValid(3, const_cast<char **>(argv.data())));
    }

    TEST(ArgumentParsingTest, HandleInvalidArgument)
    {
        server::Parser parser{};
        std::array argv = {"hello", "world"};
        EXPECT_FALSE(parser.isEveryArgValid(2, const_cast<char **>(argv.data())));
    }

    TEST(ArgumentParsingTest, HandleNotEnoughArguments)
    {
        server::Parser parser{};
        std::array argv = {"hello"};
        EXPECT_FALSE(parser.isEveryArgValid(1, const_cast<char **>(argv.data())));
    }

    TEST(ArgumentParsingTest, HandlePortTooBig)
    {
        server::Parser parser{};
        std::array argv = {"hello", "70000"};
        EXPECT_FALSE(parser.isEveryArgValid(2, const_cast<char **>(argv.data())));
    }

    TEST(ArgumentParsingTest, HandlePortTooSmall)
    {
        server::Parser parser{};
        std::array argv = {"hello", "21"};
        EXPECT_FALSE(parser.isEveryArgValid(2, const_cast<char **>(argv.data())));
    }

    TEST(ArgumentParsingTest, HandleValidPort)
    {
        server::Parser parser{};
        std::array argv = {"hello", "4444"};
        EXPECT_TRUE(parser.isEveryArgValid(2, const_cast<char **>(argv.data())));
    }

    TEST(ArgumentParsingTest, CheckParserPort)
    {
        server::Parser parser{};
        std::array argv = {"hello", "4444"};
        parser.isEveryArgValid(2, const_cast<char **>(argv.data()));
        EXPECT_EQ(4444, parser.getPort());
    }

    /* Check help tests */

    TEST(DisplayHelpTest, CheckHelp1)
    {
        server::Parser const parser{};
        std::array argv = {"hello", "-h"};
        EXPECT_EQ(parser.checkHelp(2, const_cast<char **>(argv.data())), EXIT_SUCCESS);
    }

    TEST(DisplayHelpTest, CheckHelp2)
    {
        server::Parser const parser{};
        std::array argv = {"hello", "-help"};
        EXPECT_EQ(parser.checkHelp(2, const_cast<char **>(argv.data())), EXIT_SUCCESS);
    }

    TEST(DisplayHelpTest, CheckHelp3)
    {
        server::Parser const parser{};
        std::array argv = {"hello", "--help"};
        EXPECT_EQ(parser.checkHelp(2, const_cast<char **>(argv.data())), EXIT_SUCCESS);
    }

    TEST(DisplayHelpTest, CheckInvalidArgument)
    {
        server::Parser const parser{};
        std::array argv = {"hello", "zefnzhfb"};
        EXPECT_EQ(parser.checkHelp(2, const_cast<char **>(argv.data())), EXIT_FAILURE);
    }

    TEST(DisplayHelpTest, CheckTooManyArguments)
    {
        server::Parser const parser{};
        std::array argv = {"hello", "zefnzhfb", "efhevfg"};
        EXPECT_EQ(parser.checkHelp(3, const_cast<char **>(argv.data())), EXIT_FAILURE);
    }

    TEST(DisplayHelpTest, CheckNotEnoughArguments)
    {
        server::Parser const parser{};
        std::array argv = {"hello"};
        EXPECT_EQ(parser.checkHelp(1, const_cast<char **>(argv.data())), EXIT_FAILURE);
    }
}
