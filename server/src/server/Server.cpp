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
#include <thread>
#include <utility>

namespace server {

     Server::Server(std::shared_ptr<cmn::SharedData> &data):
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

            if (_socketSelector.isReady(sock)) {
                cmn::CustomPacket packet;
                sf::Socket::Status const status = sock.receive(packet);
                if (status != sf::Socket::Status::Done) {
                    if (status == sf::Socket::Status::Disconnected || status == sf::Socket::Status::Error) {
                        _socketSelector.remove(sock);
                        _sharedData->deletePlayer(sock.getRemotePort(), sock.getRemoteAddress().value());
                        it = _socketVector.erase(it);
                    }
                }

                auto data = cmn::PacketDisassembler::disassemble(packet);

                _sharedData->addTcpReceivedPacket(data.second);
            }
        }
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

    void Server::broadcastTcp(const cmn::CustomPacket& packet) const
    {
        for (const auto &client : _socketVector) {
            if (sendTcp(packet, *client) == 1) {
            }
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
            if (sendUdp(packet, ip.value(), clientPort) == 1) {
            }
        }
    }

    void Server::_acceptConnection()
    {
        static uint32_t idPlayer = 1;
        auto client = std::make_unique<sf::TcpSocket>();

        client->setBlocking(false);

        if (_listener.accept(*client) != sf::Socket::Status::Done) {
            return;
        }
        _socketSelector.add(*client);
        _sharedData->addPlayer(static_cast<int>(idPlayer), client->getRemotePort(), client->getRemoteAddress().value());
        auto pair = std::make_pair(client->getRemotePort(), client->getRemoteAddress().value());
        _playerList.emplace(pair, idPlayer);
        cmn::clientNetworkState const clientNetworkState;
        _clientStates[idPlayer] = clientNetworkState;
        cmn::connectionData data = {idPlayer};
        cmn::CustomPacket const packet = cmn::PacketFactory::createPacket(data, _reliablePackets);
        sendTcp(packet, *client);
        _socketVector.push_back(std::move(client));
        idPlayer++;
    }

    void Server::_resendTimedOutPackets()
    {
        auto now = std::chrono::steady_clock::now();

        for (auto it = _reliablePackets.begin(); it != _reliablePackets.end(); ) {
            auto& reliablePkt = it->second;

            auto timeSinceLastSend = std::chrono::duration_cast<std::chrono::milliseconds>(
                now - reliablePkt.lastSentTime
            ).count();

            if (timeSinceLastSend > cmn::ticksBeforeResending) {
                if (reliablePkt.retryCount < cmn::reliabilityRetries) {
                    broadcastUdp(reliablePkt.packet);
                    reliablePkt.lastSentTime = now;
                    reliablePkt.retryCount++;
                    ++it;
                } else {
                    it = _reliablePackets.erase(it);
                }
            } else {
                ++it;
            }
        }
    }

    bool Server::_shouldProcessPacket(const cmn::packetHeader& header, cmn::clientNetworkState state) {
        uint32_t const incomingSeq = header.sequenceNbr;

        if (state.processedSequences.contains(incomingSeq)) {
            return false;
        }

        if ((int32_t)(incomingSeq - state.lastProcessedSequence) <= 0) {
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


    void Server::_handleUdpReception(cmn::packetHeader header, cmn::packetData data, sf::IpAddress ip, uint16_t port)
    {
        auto pair = std::make_pair(port, ip);
        uint32_t const clientId = _playerList[pair];

        if (!_shouldProcessPacket(header, _clientStates[clientId])) {
            return;
        }

        if (header.protocolId == cmn::acknowledgeProtocolId) {
            cmn::acknowledgeData const acknowledgeData = std::get<cmn::acknowledgeData>(data);
            uint32_t const sequenceNbr = acknowledgeData.sequenceNbr;
            _reliablePackets.erase(sequenceNbr);
            return;
        }

        _sharedData->addUdpReceivedPacket(data);
        _resendTimedOutPackets();
    }

    void Server::run()
    {
        _socketSelector.add(_listener);

        std::jthread const tcpThread = std::jthread{[this]{ _handleTcp(); }};

        std::optional<sf::IpAddress> sender;
        unsigned short port = 0;

        while (true) {
            cmn::CustomPacket packet;
            auto udpData = _sharedData->getUdpPacketToSend();

            if (udpData.has_value()) {
                broadcastUdp(cmn::PacketFactory::createPacket(udpData.value(), _reliablePackets));
            }

            auto tcpData = _sharedData->getTcpPacketToSend();

            if (tcpData.has_value()) {
                broadcastTcp(cmn::PacketFactory::createPacket(tcpData.value(), _reliablePackets));
            }

            if (_udpSocket.receive(packet, sender, port) != sf::Socket::Status::Done) {
                continue;
            }

            auto data = cmn::PacketDisassembler::disassemble(packet);
            _handleUdpReception(data.first, data.second, sender.value(), port);
        }
    }

}// namespace server