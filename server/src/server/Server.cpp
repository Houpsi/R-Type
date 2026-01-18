/*
** EPITECH PROJECT, 2025
** R_Type
** File description:
** Server
*/
#include "Server.hpp"

#include "SFML/Network/TcpSocket.hpp"
#include "constants/NetworkConstants.hpp"
#include "custom_packet/CustomPacket.hpp"
#include "packet_disassembler/PacketDisassembler.hpp"
#include "packet_factory/PacketFactory.hpp"
#include "packet_header/PacketHeader.hpp"

#include <iostream>
#include <iostream>
#include <thread>
#include <utility>

namespace server {
    Server::Server(const std::shared_ptr<ServerSharedData> &data):
   _sharedData(data) {}


    int Server::bindPorts(const uint16_t port)
    {
        _listener.setBlocking(false);
        _udpSocket.setBlocking(false);
        if (_listener.listen(port) != sf::Socket::Status::Done) {
            return 1;
        }
        if (_udpSocket.bind(port) != sf::Socket::Status::Done) {
            return 1;
        }
        return 0;
    }

    void Server::close()
    {
        _listener.close();
        _udpSocket.unbind();
    }

    [[noreturn]] void Server::_handleTcp()
    {
        while (true) {
            if (_socketSelector.wait()) {
                _checkSocket();
            }
        }
    }

    void Server::_checkSocket()
    {
        if (_socketSelector.isReady(_listener)) {
            _acceptConnection();
        } else {
            _handleNewTcpPacket();
        }
    }

    void Server::_handleNewTcpPacket()
    {
        for (auto it = _socketVector.begin(); it != _socketVector.end(); ) {
            auto &sock = **it;

            if (!_socketSelector.isReady(sock)) {
                ++it;
                continue;
            }

            cmn::CustomPacket packet;
            sf::Socket::Status const status = sock.receive(packet);

            if (status != sf::Socket::Status::Done) {
                if (status == sf::Socket::Status::Disconnected || status == sf::Socket::Status::Error) {
                    _socketSelector.remove(sock);
                    int const playerId = _getPlayerIdFromSocket(sock);
                    if (playerId != -1) {
                        _sharedData->deletePlayer(playerId);
                        _playerSocketMap.erase(playerId);
                        _clientStates.erase(playerId);
                    }
                    it = _socketVector.erase(it);
                    std::cout << "Player " << playerId << " removed" << std::endl;
                    continue;
                }
                ++it;
                continue;
            }
            if (int const playerId = _getPlayerIdFromSocket(sock); playerId != -1) {
                auto data = cmn::PacketDisassembler::disassemble(packet);
                _routePacket(data.second, playerId);
            }
            ++it;
        }
    }

    void Server::_routePacket(const cmn::packetData& packet, const int playerId) const
    {
        if (_isSystemPacket(packet)) {
            _sharedData->addSystemPacket(packet);
            return;
        }
        int const lobbyId = _sharedData->getPlayerLobby(playerId);
        if (lobbyId != -1) {
            _sharedData->addLobbyTcpReceivedPacket(lobbyId, packet);
        }
    }

    bool Server::_isSystemPacket(const cmn::packetData& data)
    {
        return std::visit([](auto &&arg) -> bool {
            using T = std::decay_t<decltype(arg)>;
            return std::is_same_v<T, cmn::selectModeData> ||
                          std::is_same_v<T, cmn::requestJoinLobbyData> ||
                          std::is_same_v<T, cmn::leaveLobbyData>;
        }, data);
    }

    int Server::_getPlayerIdFromSocket(const sf::TcpSocket& socket) const
    {
        const auto port = socket.getRemotePort();
        const auto ip = socket.getRemoteAddress();

        if (!ip.has_value()) {
            return -1;
        }
        for (auto player : _sharedData->getMapPlayers()) {
            if (std::cmp_equal(player.second.first , port) &&
                player.second.second == ip.value()) {
                return player.first;
                }
        }
        return -1;
    }

    int Server::_getPlayerIdFromUdp(const sf::IpAddress &ip, unsigned short port) const
    {
        for (const auto& [playerId, playerInfo] : _sharedData->getMapPlayers()) {
            if (std::cmp_equal(playerInfo.first, port) && playerInfo.second == ip) {
                return playerId;
            }
        }
        return -1;
    }

    int Server::sendUdp(cmn::CustomPacket packet, const sf::IpAddress& clientIp, uint16_t port)
    {
        sf::Socket::Status const status = _udpSocket.send(packet, clientIp, port);
        if (status != sf::Socket::Status::Done) {
            return 1;
        }
        return 0;
    }

    int Server::sendTcp(cmn::CustomPacket packet, sf::TcpSocket& clientSocket)
    {
        sf::Socket::Status const status = clientSocket.send(packet);
        if (status != sf::Socket::Status::Done) {
            return 1;
        }
        return 0;
    }

    void Server::sendTcpToPlayer(int playerId, const cmn::CustomPacket& packet)
    {
        auto it = _playerSocketMap.find(playerId);
        if (it != _playerSocketMap.end() && it->second) {
            sendTcp(packet, *it->second);
        }
    }

    void Server::broadcastTcp(const cmn::CustomPacket& packet) const
    {
        for (const auto &client : _socketVector) {
            sendTcp(packet, *client);
        }
    }

    void Server::broadcastUdp(const cmn::CustomPacket& packet)
    {
        for (const auto &client : _socketVector) {
            auto ip = client->getRemoteAddress();
            const auto clientPort = client->getRemotePort();
            if (!ip.has_value() || clientPort == 0) {
                continue;
            }
            sendUdp(packet, ip.value(), clientPort);
            }
        }

    void Server::broadcastTcpToLobby(const int lobbyId, const cmn::CustomPacket& packet)
    {
        auto const playerIds = _sharedData->getLobbyPlayers(lobbyId);

        for (int const playerId : playerIds) {
            auto it = _playerSocketMap.find(playerId);
            if (it != _playerSocketMap.end() && it->second) {
                sendTcp(packet, *it->second);
            }
        }
    }

    void Server::broadcastUdpToLobby(const int lobbyId, const cmn::CustomPacket& packet)
{
    auto const playerIds = _sharedData->getLobbyPlayers(lobbyId);

    for (int const playerId : playerIds) {
        auto playerInfo = _sharedData->getPlayer(playerId);
        if (playerInfo.has_value()) {
            sendUdp(packet, playerInfo->second, playerInfo->first);
        }
    }
}


    void Server::_acceptConnection()
    {
        static uint32_t idPlayer = 1;
        auto client = std::make_shared<sf::TcpSocket>();

        client->setBlocking(false);

        if (_listener.accept(*client) != sf::Socket::Status::Done) {
            return;
        }
        _socketSelector.add(*client);

        _playerSocketMap[idPlayer] = client;
        _sharedData->addPlayer(idPlayer, client->getRemotePort(), client->getRemoteAddress().value(), client);
        auto pair = std::make_pair(client->getRemotePort(), client->getRemoteAddress().value());
        _playerList.emplace(pair, idPlayer);
        cmn::clientNetworkState const clientNetworkState;
        _clientStates[idPlayer] = clientNetworkState;
        cmn::connectionData data = {idPlayer};
        std::unordered_map<uint32_t, cmn::reliablePacket> emptyMap;
        cmn::CustomPacket const packet = cmn::PacketFactory::createPacket(data, emptyMap);
        sendTcp(packet, *client);
        _socketVector.push_back(client);
        std::cout << "New player " << idPlayer << " accepted" << std::endl;
        idPlayer++;
    }

    void Server::_processLobbyPackets()
    {
        std::vector<int> const lobbyIds = _sharedData->getAllLobbyIds();

        for (int const lobbyId : lobbyIds) {
            auto tcpData = _sharedData->getLobbyTcpPacketToSend(lobbyId);
            if (tcpData.has_value()) {
                std::unordered_map<uint32_t, cmn::reliablePacket> emptyMap;
                cmn::CustomPacket const packet = cmn::PacketFactory::createPacket(tcpData.value(), emptyMap);
                broadcastTcpToLobby(lobbyId, packet);
            }
            auto udpData = _sharedData->getLobbyUdpPacketToSend(lobbyId);
            if (udpData.has_value()) {
                if (!_lobbyReliablePackets.contains(lobbyId)) {
                    _lobbyReliablePackets[lobbyId] = std::unordered_map<uint32_t, cmn::reliablePacket>();
                }
                cmn::CustomPacket const packet = cmn::PacketFactory::createPacket(
                    udpData.value(),
                    _lobbyReliablePackets[lobbyId]
                );
                broadcastUdpToLobby(lobbyId, packet);
            }
            _resendTimedOutPackets(lobbyId);
        }
        auto tcpSinglePlayer = _sharedData->getTcpPacketToSendToSpecificPlayer();
        if (tcpSinglePlayer.has_value()) {
            std::unordered_map<uint32_t, cmn::reliablePacket> emptyMap;
            cmn::CustomPacket const packet = cmn::PacketFactory::createPacket(tcpSinglePlayer->second, emptyMap);
            sendTcpToPlayer(tcpSinglePlayer->first, packet);
        }
    }

    void Server::_resendTimedOutPackets(int lobbyId)
    {
        if (!_lobbyReliablePackets.contains(lobbyId)) {
            return;
        }

        const auto now = std::chrono::steady_clock::now();

        for (auto it = _lobbyReliablePackets[lobbyId].begin(); it != _lobbyReliablePackets[lobbyId].end(); ) {
            auto& reliablePkt = it->second;

            const auto timeSinceLastSend = std::chrono::duration_cast<std::chrono::milliseconds>(
                now - reliablePkt.lastSentTime
            ).count();

            if (timeSinceLastSend > cmn::ticksBeforeResending) {
                if (reliablePkt.retryCount < cmn::reliabilityRetries) {
                    broadcastUdpToLobby(lobbyId, reliablePkt.packet);
                    reliablePkt.lastSentTime = now;
                    reliablePkt.retryCount++;
                    ++it;
                } else {
                    it = _lobbyReliablePackets[lobbyId].erase(it);
                }
            } else {
                ++it;
            }
        }
    }

    bool Server::_shouldProcessPacket(const cmn::packetHeader& header, cmn::clientNetworkState &state) {
        uint32_t const incomingSeq = header.sequenceNbr;

        if (state.processedSequences.contains(incomingSeq)) {
            return false;
        }

        if (static_cast<int32_t>(incomingSeq - state.lastProcessedSequence) <= 0) {
            return false;
        }

        state.lastProcessedSequence = incomingSeq;
        state.processedSequences.insert(incomingSeq);

        if (state.processedSequences.size() > cmn::maxSequences) {
            for (auto it = state.processedSequences.begin(); it != state.processedSequences.end();) {
                if (std::cmp_less((*it - state.lastProcessedSequence), cmn::maxSequenceDiff)) {
                    it = state.processedSequences.erase(it);
                } else {
                    ++it;
                }
            }
        }

        return true;
    }


    void Server::_handleUdpReception(
        const cmn::packetHeader header,
        const cmn::packetData &data,
        sf::IpAddress ip,
        uint16_t port,
        const int lobbyId)
    {
        const auto pair = std::make_pair(port, ip);
        uint32_t const clientId = _playerList[pair];

        if (!_shouldProcessPacket(header, _clientStates[clientId])) {
            return;
        }

        if (header.protocolId == cmn::acknowledgeProtocolId) {
            cmn::acknowledgeData const acknowledgeData = std::get<cmn::acknowledgeData>(data);
            uint32_t const sequenceNbr = acknowledgeData.sequenceNbr;

            if (_lobbyReliablePackets.contains(lobbyId)) {
                _lobbyReliablePackets[lobbyId].erase(sequenceNbr);
            }
            return;
        }
        _sharedData->addLobbyUdpReceivedPacket(lobbyId, data);
    }

    void Server::run()
    {
        _socketSelector.add(_listener);

        auto const tcpThread = std::jthread{[this]{ _handleTcp(); }};

        std::optional<sf::IpAddress> sender;
        unsigned short port = 0;
        cmn::CustomPacket packet;

        while (true) {
            _processLobbyPackets();
            if (_udpSocket.receive(packet, sender, port) == sf::Socket::Status::Done) {
                if (!sender.has_value()) {
                    continue;
                }
                auto data = cmn::PacketDisassembler::disassemble(packet);
                int playerId = _getPlayerIdFromUdp(sender.value(), port);
                if (playerId != -1) {
                    int lobbyId = _sharedData->getPlayerLobby(playerId);
                    if (lobbyId != -1) {
                        _handleUdpReception(data.first, data.second, sender.value(), port, lobbyId);
                    }
                }
            }
        }
    }
}// namespace server