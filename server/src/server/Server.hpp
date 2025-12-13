/*
** EPITECH PROJECT, 2025
** R_Type
** File description:
** Server
*/
#ifndef R_TYPE_SERVER_HPP
#define R_TYPE_SERVER_HPP

#include "packet_data/PacketData.hpp"
#include "SFML/Network/SocketSelector.hpp"
#include "SFML/Network/UdpSocket.hpp"
#include "shared_data/SharedData.hpp"
#include <SFML/Network/TcpListener.hpp>
#include <SFML/Network/TcpSocket.hpp>
#include <thread>

namespace server {

    class Server
    {
      public:
        explicit Server(const std::shared_ptr<cmn::SharedData> &data);
        Server();
        [[nodiscard]]int bindPorts(uint16_t port);
        void close();
        [[noreturn]] void run();

        int sendUdp(const cmn::packetData& packet, const sf::IpAddress& clientIp, uint16_t port);
        static int sendTcp(const cmn::packetData& packet, sf::TcpSocket& clientSocket);

        int broadcastUdp(const cmn::packetData&packet, uint16_t port);
        int broadcastTcp(const cmn::packetData& packet)const;

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
        std::shared_ptr<cmn::SharedData> _sharedData;
    };

}// namespace server

#endif// R_TYPE_SERVER_HPP
