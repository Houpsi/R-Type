/*
** EPITECH PROJECT, 2025
** r-type_server
** File description:
** main
*/

#include "game/Game.hpp"
#include "parser/Parser.hpp"
#include "server/Server.hpp"

int main(int argc, char **argv)
{
    server::Parser parser{};

    if (!parser.isEveryArgValid(argc, argv)) {
        return parser.checkHelp(argc, argv);
    }

    const std::shared_ptr<cmn::SharedData> data;
    server::Server server(data);

    uint16_t const port = parser.getPort();
    if (server.bindPorts(port) != 0) {
        return EXIT_FAILURE;
    }

    server::Game game(data);
    auto  networkThread = std::jthread([&server] {server.run();});
    game.run();
    return EXIT_SUCCESS;
}


