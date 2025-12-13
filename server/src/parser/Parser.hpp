/*
** EPITECH PROJECT, 2025
** r-type_server
** File description:
** Parser
*/
#ifndef R_TYPE_SERVER_PARSER_HPP
#define R_TYPE_SERVER_PARSER_HPP
#include "parser/AParser.hpp"

namespace server {
    class Parser final : public AParser
    {
      public:
        Parser() = default;
        bool isEveryArgValid(int argc, char **args) override;
      private:
        void _displayHelp() const override;
    };

}// namespace server

#endif// R_TYPE_SERVER_PARSER_HPP
