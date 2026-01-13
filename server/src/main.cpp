/*
** EPITECH PROJECT, 2025
** r-type_server
** File description:
** main
*/

#include "game/Game.hpp"
#include "lobby_manager/LobbyManager.hpp"
#include "parser/Parser.hpp"
#include "server/Server.hpp"
#include <iostream>

int main(int argc, char **argv)
{
    server::Parser parser{};

    if (!parser.isEveryArgValid(argc, argv)) {
        return parser.checkHelp(argc, argv);
    }

    auto data = std::make_shared<server::ServerSharedData>();
    server::Server server(data);

    uint16_t const port = parser.getPort();
    if (server.bindPorts(port) != 0) {
        return EXIT_FAILURE;
    }

    try {
        server::LobbyManager lobby_manager(data);
        auto  networkThread = std::jthread([&server] {server.run();});
        lobby_manager.run();
    } catch (std::exception &e) {
        return EXIT_FAILURE;
    }

}

