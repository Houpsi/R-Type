/*
** EPITECH PROJECT, 2025
** R_Type
** File description:
** AParser
*/

#include "AParser.hpp"
#include <cstdlib>
#include <iostream>
#include <ostream>
#include <span>
#include <string_view>

uint16_t AParser::getPort() const
{
    return this->port;
}

int AParser::checkHelp(int argc, char **argv) const
{
    if (argc != 2) {
        _displayHelp();
        return EXIT_FAILURE;
    }
    auto arguments = std::span<char *>(argv, argc);
    std::string_view const stringView(arguments[1]);
    if (stringView == "-h" || stringView == "-help" || stringView == "--help") {
        _displayHelp();
        return EXIT_SUCCESS;
    }
    _displayHelp();
    return EXIT_FAILURE;
}

bool AParser::isEveryArgValid(int argc, char **args)
{
    (void)argc;
    (void)args;
    return true;
}

void AParser::_displayHelp() const
{
    std::cout << '\n';
}