/*
** EPITECH PROJECT, 2025
** R_Type
** File description:
** TestServer
*/
#include  "SFML/Network/TcpListener.hpp"
#include "server/Server.hpp"
#include <SFML/Network/Socket.hpp>
#include <SFML/Network/TcpSocket.hpp>
#include <gtest//gtest.h>
#include <thread>

namespace test {

    /* Server binding tests */

    TEST(ServerBindingTest, HandleAlreadyUsedPortTcp)
    {
        constexpr uint16_t port = 4444;

        server::Server server{};
        sf::TcpListener listener;
        if (listener.listen(port) != sf::Socket::Status::Done) {}
        EXPECT_EQ(server.bindPorts(port), 1);
        listener.close();
    }

    TEST(ServerBindingTest, HandleAlreadyUsedPortUdp)
    {
        constexpr uint16_t port = 4444;

        server::Server server{};
        sf::UdpSocket udpSocket;
        if (udpSocket.bind(port) != sf::Socket::Status::Done) {}
        EXPECT_EQ(server.bindPorts(port), 1);
        udpSocket.unbind();
    }

    TEST(ServerBindingTest, HandleInvalidPortTcp)
    {
        constexpr uint16_t port = 1000;

        server::Server server{};
        EXPECT_EQ(server.bindPorts(port), 1);
    }

    TEST(ServerBindingTest, HandleInvalidPortUdp)
    {
        constexpr uint16_t port = 1000;

        server::Server server{};
        EXPECT_EQ(server.bindPorts(port), 1);
    }

    TEST(ServerBindingTest, HandleValidPort)
    {
        constexpr uint16_t port = 4444;

        server::Server server{};
        EXPECT_EQ(server.bindPorts(port), 0);
    }

}
