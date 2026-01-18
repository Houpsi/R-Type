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
#include "client_shared_data/ClientSharedData.hpp"
#include "client_network_state/ClientNetworkState.hpp"
#include "packet_data/PacketData.hpp"
#include "packet_header/PacketHeader.hpp"
#include "reliable_packet/ReliablePacket.hpp"

#include <thread>
#include <unordered_map>

namespace client {

    class Client
    {
        public:
            explicit Client(const std::shared_ptr<ClientSharedData> &data);
            [[nodiscard]] int bindPorts();
            [[nodiscard]] int connectToHost(const std::string &address, uint16_t port);
            int run();

            int sendUdp(cmn::CustomPacket packet);
            int sendTcp(cmn::CustomPacket packet);

        private:
            sf::TcpSocket _tcpSocket;
            sf::UdpSocket _udpSocket;

            sf::IpAddress _serverIp = sf::IpAddress::LocalHost;
            uint16_t _serverUdpPort = 0;
            std::jthread _tcpThread;

            std::shared_ptr<ClientSharedData> _sharedData;
            std::unordered_map<uint32_t, cmn::reliablePacket> _reliablePackets;

            void _handleTcp();
            void _handleUdpReception(cmn::packetHeader header, cmn::packetData data);
            void _resendTimedOutPackets();
            void _sendAckPacket(cmn::packetHeader header);
            static bool _shouldProcessPacket(const cmn::packetHeader &header,
                cmn::clientNetworkState &state);
            cmn::clientNetworkState _serverState;
    };
}

#endif //R_TYPE_CLIENT_HPP
