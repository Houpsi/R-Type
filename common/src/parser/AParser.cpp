/*
** EPITECH PROJECT, 2025
** R_Type
** File description:
** AParser
*/

#include "AParser.hpp"
#include <cstdlib>
#include <span>
#include <string_view>

uint16_t AParser::getPort() const
{
    return this->port;
}

int AParser::checkHelp(int argc, char **args)
{
    if (argc != 2) {
        _displayHelp();
        return EXIT_FAILURE;
    }
    auto arguments = std::span<char *>(args, argc);
    std::string_view const stringView(arguments[1]);
    if (stringView == "-h" || stringView == "-help" || stringView == "--help") {
        _displayHelp();
        return EXIT_SUCCESS;
    }
    _displayHelp();
    return EXIT_FAILURE;
}