/*
** EPITECH PROJECT, 2025
** R_Type
** File description:
** main
*/

#include "client/Client.hpp"
#include "game_renderer/GameRenderer.hpp"
#include "parser/Parser.hpp"
#include "shared_data/SharedData.hpp"

#include <iostream>

int main(const int argc, char *argv[])
{
    client::Parser parser{};

    if (!parser.isEveryArgValid(argc, argv)) {
        return parser.checkHelp(argc, argv);
    }

    std::shared_ptr<cmn::SharedData> const data;

    client::Client client(data);

    uint16_t const serverPort = parser.getPort();
    const std::string serverIp = parser.getIp();

    if (client.bindPorts(0) != 0) {
        std::cerr << "Fatal Error: Client failed to bind local ports.\n";
        return EXIT_FAILURE;
    }

    if (client.connectToHost(serverIp, serverPort) != 0) {
        return EXIT_FAILURE;
    }

    client::GameRenderer game(data);
    auto  networkThread = std::jthread([&client] {client.run();});
    game.run();
    return EXIT_SUCCESS;
}