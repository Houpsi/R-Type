/*
** EPITECH PROJECT, 2025
** R_Type
** File description:
** Server
*/

#ifndef R_TYPE_SERVER_HPP
#define R_TYPE_SERVER_HPP

#include "SFML/Network/IpAddress.hpp"
#include "SFML/Network/SocketSelector.hpp"
#include "SFML/Network/TcpListener.hpp"
#include "SFML/Network/TcpSocket.hpp"
#include "SFML/Network/UdpSocket.hpp"
#include "client_network_state/ClientNetworkState.hpp"
#include "custom_packet/CustomPacket.hpp"
#include "packet_data/PacketData.hpp"
#include "packet_header/PacketHeader.hpp"
#include "reliable_packet/ReliablePacket.hpp"
#include "server_shared_data/ServerSharedData.hpp"
#include <map>
#include <memory>
#include <thread>
#include <vector>

namespace server {
    class Server {
    public:
        explicit Server(const std::shared_ptr<ServerSharedData> &data);

        int bindPorts(uint16_t port);
        void close();
        [[noreturn]] void run();

        int sendUdp(cmn::CustomPacket packet, const sf::IpAddress &clientIp, uint16_t port);
        static int sendTcp(cmn::CustomPacket packet, sf::TcpSocket &clientSocket);
        void sendTcpToPlayer(int playerId, const cmn::CustomPacket &packet);
        void broadcastTcp(const cmn::CustomPacket &packet) const;
        void broadcastUdp(const cmn::CustomPacket &packet);
        void broadcastTcpToLobby(int lobbyId, const cmn::CustomPacket &packet);
        void broadcastUdpToLobby(int lobbyId, const cmn::CustomPacket &packet);

    private:
        [[noreturn]] void _handleTcp();
        void _checkSocket();
        void _handleNewTcpPacket();
        void _handleUdpReception(cmn::packetHeader header,
            const cmn::packetData &data, sf::IpAddress ip, uint16_t port, int lobbyId);
        void _resendTimedOutPackets(int lobbyId);
        void _acceptConnection();
        void _processLobbyPackets();
        void _routePacket(const cmn::packetData &packet, int playerId) const;
        int _getPlayerIdFromSocket(const sf::TcpSocket &socket) const;
        int _getPlayerIdFromUdp(const sf::IpAddress &ip, unsigned short port) const;
        static bool _isSystemPacket(const cmn::packetData &data);
        static bool _shouldProcessPacket(const cmn::packetHeader &header, cmn::clientNetworkState &state);

        sf::TcpListener _listener;
        sf::UdpSocket _udpSocket;
        sf::SocketSelector _socketSelector;
        std::vector<std::shared_ptr<sf::TcpSocket>> _socketVector;
        std::unordered_map<int, std::shared_ptr<sf::TcpSocket>> _playerSocketMap;
        std::jthread _tcpThread;
        std::shared_ptr<ServerSharedData> _sharedData;
        std::map<std::pair<uint16_t, sf::IpAddress>, uint32_t> _playerList;
        std::unordered_map<uint32_t, cmn::clientNetworkState> _clientStates;
        std::unordered_map<int, std::unordered_map<uint32_t, cmn::reliablePacket>> _lobbyReliablePackets;
    };

}// namespace server

#endif// R_TYPE_SERVER_HPP
