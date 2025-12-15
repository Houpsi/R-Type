/*
** EPITECH PROJECT, 2025
** R_Type
** File description:
** TestClient
*/


#include "SFML/Network/TcpListener.hpp"
#include "client/Client.hpp"


#include <chrono>
#include <gtest/gtest.h>
#include <memory>
#include <thread>

TEST(ClientTest, BindPortsSuccess)
{
    auto sharedData = std::make_shared<cmn::SharedData>();
    client::Client client(sharedData);

    uint16_t port = 55001;
    int result = client.bindPorts();

    EXPECT_EQ(result, 0);
}

TEST(ClientTest, BindPortsFailWhenPortAlreadyUsed)
{
    auto sharedData = std::make_shared<cmn::SharedData>();
    client::Client client1(sharedData);
    client::Client client2(sharedData);

    uint16_t port = 55002;

    ASSERT_EQ(client1.bindPorts(), 0);
    EXPECT_EQ(client2.bindPorts(), 1);
}

TEST(ClientTest, ConnectToHostSuccess)
{
    sf::TcpListener listener;
    uint16_t port = 55010;
    ASSERT_EQ(listener.listen(port), sf::Socket::Status::Done);

    std::thread serverThread([&]() {
        sf::TcpSocket socket;
        sf::Socket::Status a = listener.accept(socket);
    });

    auto sharedData = std::make_shared<cmn::SharedData>();
    client::Client client(sharedData);

    int result = client.connectToHost("127.0.0.1", port);
    EXPECT_EQ(result, 0);

    serverThread.join();
}

TEST(ClientTest, ConnectToHostInvalidAddress)
{
    auto sharedData = std::make_shared<cmn::SharedData>();
    client::Client client(sharedData);

    int result = client.connectToHost("invalid.host.name", 12345);

    EXPECT_EQ(result, 1);
}

TEST(ClientTest, SendTcpSuccess)
{
    sf::TcpListener listener;
    uint16_t port = 55020;
    ASSERT_EQ(listener.listen(port), sf::Socket::Status::Done);

    sf::TcpSocket serverSocket;

    std::thread serverThread([&]() {
        sf::Socket::Status a = listener.accept(serverSocket);
        sf::Packet packet;
        sf::Socket::Status b = serverSocket.receive(packet);
    });

    auto sharedData = std::make_shared<cmn::SharedData>();
    client::Client client(sharedData);
    ASSERT_EQ(client.connectToHost("127.0.0.1", port), 0);

    cmn::packetData data {};
    data.packetId = 1;

    int result = client.sendTcp(data);
    EXPECT_EQ(result, 0);

    serverThread.join();
}

TEST(ClientTest, SendUdpSuccess)
{
    uint16_t port = 55030;

    // TCP server
    sf::TcpListener tcpListener;
    ASSERT_EQ(tcpListener.listen(port), sf::Socket::Status::Done);

    std::thread tcpThread([&]() {
        sf::TcpSocket socket;
        sf::Socket::Status a = tcpListener.accept(socket);
    });

    // UDP server
    sf::UdpSocket udpSocket;
    ASSERT_EQ(udpSocket.bind(port), sf::Socket::Status::Done);

    auto sharedData = std::make_shared<cmn::SharedData>();
    client::Client client(sharedData);

    ASSERT_EQ(client.bindPorts(), 0);
    ASSERT_EQ(client.connectToHost("127.0.0.1", port), 0);

    std::thread udpThread([&]() {
        sf::Packet packet;
        std::optional<sf::IpAddress> sender;
        unsigned short senderPort;
        sf::Socket::Status b = udpSocket.receive(packet, sender, senderPort);
    });

    cmn::packetData data {};
    data.packetId = 2;
    cmn::CustomPacket packet;
    packet << data;

    EXPECT_EQ(client.sendUdp(packet), 0);

    udpThread.join();
    tcpThread.join();
}

