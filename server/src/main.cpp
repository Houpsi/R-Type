/*
** EPITECH PROJECT, 2025
** r-type_server
** File description:
** main
*/

#include "game/Game.hpp"
#include "parser/Parser.hpp"
#include "server/Server.hpp"
#include <iostream>

int main(int argc, char **argv)
{
    server::Parser parser{};

    if (!parser.isEveryArgValid(argc, argv)) {
        return parser.checkHelp(argc, argv);
    }

    auto data = std::make_shared<cmn::SharedData>();
    server::Server server(data);

    uint16_t const port = parser.getPort();
    if (server.bindPorts(port) != 0) {
        return EXIT_FAILURE;
    }

    try {
        server::Game game(data);
        auto  networkThread = std::jthread([&server] {server.run();});
        game.run();
    } catch (std::exception &e) {
        return EXIT_FAILURE;
    }

}


