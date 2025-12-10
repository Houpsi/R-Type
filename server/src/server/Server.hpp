/*
** EPITECH PROJECT, 2025
** R_Type
** File description:
** Server
*/
#ifndef R_TYPE_SERVER_HPP
#define R_TYPE_SERVER_HPP

#include "SFML/Network/SocketSelector.hpp"
#include "SFML/Network/UdpSocket.hpp"
#include <SFML/Network/TcpListener.hpp>
#include <SFML/Network/TcpSocket.hpp>
#include <thread>

namespace server {

    class Server
    {
      public:
        Server() = default;
        int bindPorts(uint16_t port);
        void close();
        [[noreturn]] void run();

      private:
        sf::TcpListener _listener;
        std::vector<std::unique_ptr<sf::TcpSocket>> _socketVector;
        sf::SocketSelector _socketSelector;
        void _acceptConnection();
        sf::UdpSocket _udpSocket;
        [[noreturn]] void _handleTcp();
        std::jthread _tcpThread;
        void _checkSocket();
        void _handleNewTcpPacket();
    };

}// namespace server

#endif// R_TYPE_SERVER_HPP
