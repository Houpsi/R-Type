/*
** EPITECH PROJECT, 2025
** r-type_server
** File description:
** main
*/
#include "parser/Parser.hpp"
#include "server/Server.hpp"

int main(int argc, char **argv)
{
    server::Parser parser{};

    if (!parser.isEveryArgValid(argc, argv)) {
        return parser.checkHelp(argc, argv);
    }

    server::Server server{};

    uint16_t const port = parser.getPort();
    if (server.bindPorts(port) != 0) {
        return EXIT_FAILURE;
    }
    server.run();
}


