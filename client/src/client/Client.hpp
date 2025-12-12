/*
** EPITECH PROJECT, 2025
** R_Type
** File description:
** Client
*/

#ifndef R_TYPE_CLIENT_HPP
#define R_TYPE_CLIENT_HPP
#include "custom_packet/CustomPacket.hpp"
#include "SFML/Network/TcpSocket.hpp"
#include "SFML/Network/UdpSocket.hpp"

#include <thread>

namespace client {

    class Client
    {
        public:
            [[nodiscard]]int bindPorts(uint16_t port);
            [[nodiscard]] int connectToHost(const std::string &address, uint16_t port);
            [[noreturn]] int run();

            int sendUdp(const cmn::CustomPacket& packet, const sf::IpAddress& recipient, uint16_t port);
            int sendTcp(const cmn::CustomPacket& packet);

        private:
            sf::TcpSocket _socket;
            sf::UdpSocket _udpSocket;

            sf::IpAddress _serverIp = sf::IpAddress::LocalHost;
            uint16_t _serverUdpPort = 0;
    };
}

#endif //R_TYPE_CLIENT_HPP
