/*
** EPITECH PROJECT, 2025
** R_Type
** File description:
** Parser
*/

#ifndef R_TYPE_PARSER_HPP
#define R_TYPE_PARSER_HPP

#include "parser/AParser.hpp"

#include <string>

namespace client {
    class Parser final : public AParser
    {
    public:
        Parser() = default;
        bool isEveryArgValid(int argc, char **args) override;
        [[nodiscard]] std::string getIp() const;
    private:
        void _displayHelp() const override;
        static bool _isValidIp(const std::string &ip);
        static bool _isValidIpPart(const std::string &s);
        std::string _ip;
    };
}


#endif //R_TYPE_PARSER_HPP
