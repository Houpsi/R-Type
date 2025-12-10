/*
** EPITECH PROJECT, 2025
** r-type_server
** File description:
** Parser
*/
#ifndef R_TYPE_SERVER_PARSER_HPP
#define R_TYPE_SERVER_PARSER_HPP

#include <cstdint>
namespace server {

    class Parser
    {
      public:
        Parser() = default;
        bool isEveryArgValid(int argc, char **args);
        static int checkHelp(int argc, char **argv);
        [[nodiscard]] uint16_t getPort() const;
      private:
        uint16_t port;
        static void _displayHelp();
    };

}// namespace server

#endif// R_TYPE_SERVER_PARSER_HPP
