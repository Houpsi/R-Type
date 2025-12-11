/*
** EPITECH PROJECT, 2025
** R_Type
** File description:
** AParser
*/

#ifndef R_TYPE_APARSER_HPP
#define R_TYPE_APARSER_HPP
#include <cstdint>

class AParser
{
    public:
        virtual ~AParser() = default;
        AParser() = default;
        virtual bool isEveryArgValid(int argc, char **args);
        int checkHelp(int argc, char **argv);
        [[nodiscard]] uint16_t getPort() const;
    protected:
        std::uint16_t port;
        virtual void _displayHelp();
};

#endif //R_TYPE_APARSER_HPP
