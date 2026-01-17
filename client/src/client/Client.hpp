/*
** EPITECH PROJECT, 2025
** R_Type
** File description:
** Client
*/

#ifndef R_TYPE_CLIENT_HPP
#define R_TYPE_CLIENT_HPP
#include "SFML/Network/SocketSelector.hpp"
#include "SFML/Network/TcpSocket.hpp"
#include "SFML/Network/UdpSocket.hpp"
#include "packet_data/PacketData.hpp"
#include "packet_header/PacketHeader.hpp"
#include "reliable_packet/ReliablePacket.hpp"
#include "shared_data/SharedData.hpp"

#include <thread>

namespace client {

    class Client
    {
        public:
            explicit Client(const std::shared_ptr<cmn::SharedData> &data);
            [[nodiscard]] int bindPorts();
            [[nodiscard]] int connectToHost(const std::string &address, uint16_t port);
            [[noreturn]] int run();

            int sendUdp(cmn::CustomPacket packet);
            int sendTcp(cmn::CustomPacket packet);

        private:
            sf::TcpSocket _tcpSocket;
            sf::UdpSocket _udpSocket;

            sf::IpAddress _serverIp = sf::IpAddress::LocalHost;
            uint16_t _serverUdpPort = 0;

            void _handleTcp();
            std::jthread _tcpThread;

            std::shared_ptr<cmn::SharedData> _sharedData;
            std::unordered_map<uint32_t, cmn::reliablePacket> _reliablePackets;
            void _handleUdpReception(cmn::packetHeader header, cmn::packetData data);
            void _resendTimedOutPackets();
            void _sendAckPacket(cmn::packetHeader header);
    };
}

#endif //R_TYPE_CLIENT_HPP
