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
#include "custom_packet/CustomPacket.hpp"
#include "packet_data/PacketData.hpp"
#include "shared_data/SharedData.hpp"
#include <SFML/Network/TcpListener.hpp>
#include <SFML/Network/TcpSocket.hpp>
#include <thread>

namespace server {

    class Server
    {
      public:
        explicit Server(std::shared_ptr<cmn::SharedData> &data);
        [[nodiscard]]int bindPorts(uint16_t port);
        void close();
        [[noreturn]] void run();

        int sendUdp(cmn::CustomPacket packet, const sf::IpAddress& clientIp, uint16_t port);
        static int sendTcp(cmn::CustomPacket packet, sf::TcpSocket& clientSocket);
        void broadcastUdp(const cmn::CustomPacket& packet);
        void broadcastTcp(const cmn::CustomPacket& packet)const;

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
