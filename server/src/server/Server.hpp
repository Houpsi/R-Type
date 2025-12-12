/*
** EPITECH PROJECT, 2025
** R_Type
** File description:
** Server
*/
#ifndef R_TYPE_SERVER_HPP
#define R_TYPE_SERVER_HPP

#include "custom_packet/CustomPacket.hpp"
#include "game/Game.hpp"
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
        [[nodiscard]]int bindPorts(uint16_t port);
        void close();
        [[noreturn]] void run();

        int sendUdp(const cmn::CustomPacket& packet, const sf::IpAddress& recipient, uint16_t port);
        int sendTcp(const cmn::CustomPacket& packet);

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
