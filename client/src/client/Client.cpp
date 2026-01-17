/*
** EPITECH PROJECT, 2025
** R_Type
** File description:
** Client
*/

#include "Client.hpp"
#include "client_network_state/ClientNetworkState.hpp"
#include "constants/NetworkConstants.hpp"
#include "custom_packet/CustomPacket.hpp"
#include "packet_disassembler/PacketDisassembler.hpp"
#include "packet_factory/PacketFactory.hpp"
#include <SFML/Network/IpAddress.hpp>
#include <SFML/Network/TcpSocket.hpp>
#include <cstdint>
#include <iostream>
#include <utility>

namespace client {

     Client::Client(const std::shared_ptr<cmn::SharedData> &data):
        _sharedData(data) {}

    int Client::bindPorts()
    {
        _udpSocket.setBlocking(false);
        if (_udpSocket.bind(_tcpSocket.getLocalPort()) != sf::Socket::Status::Done) {
            return 1;
        }
        return 0;
    }

    int Client::connectToHost(const std::string &address, const uint16_t port)
    {
        const std::optional<sf::IpAddress> ipAddress = sf::IpAddress::resolve(address);

        if (!ipAddress.has_value()) {
            std::cerr << "[ERROR]: Failed to resolve IP address or hostname: " << address << "\n";
            return 1;
        }
        std::cout << "[CONNECTION]: Connecting to " << address << ":" << port << " (TCP)\n";
        if (_tcpSocket.connect(ipAddress.value(), port) != sf::Socket::Status::Done) {
            std::cerr << "[ERROR]: Failed to connect to host via TCP.\n";
            return 1;
        }
        _serverIp = ipAddress.value();
        _serverUdpPort = port;
        std::cout << "[CONNECTION]: TCP connection established.\n";
        return 0;
    }

    int Client::sendTcp(cmn::CustomPacket packet)
    {
        if (_tcpSocket.send(packet) != sf::Socket::Status::Done) {
            std::cerr << "[ERROR]: Failed to send TCP packet.\n";
            return 1;
        }
        return 0;
    }

    int Client::sendUdp(cmn::CustomPacket packet)
    {
        if (_udpSocket.send(packet, _serverIp, _serverUdpPort) != sf::Socket::Status::Done) {
            std::cerr << "[ERROR]: Failed to send UDP packet.\n";
            return 1;
        }
        return 0;
    }

    void Client::_handleTcp()
    {
        sf::SocketSelector selector;
        selector.add(_tcpSocket);
        cmn::CustomPacket packet;
        constexpr int waitTime = 50;

        while (true) {
            if (!selector.wait(sf::milliseconds(waitTime))) {
                continue;
            }
            if (selector.isReady(_tcpSocket)) {
                sf::Socket::Status const status = _tcpSocket.receive(packet);
                if (status == sf::Socket::Status::Disconnected) {
                    std::cerr << "[TCP]: Server disconnected.\n";
                    break;
                }
                if (status != sf::Socket::Status::Done) {
                    std::cerr << "[TCP]: Failed to receive TCP packet.\n";
                    continue;
                }

                auto data = cmn::PacketDisassembler::disassemble(packet);

                _sharedData->addTcpReceivedPacket(data.second);
            }
        }
    }

    void Client::_resendTimedOutPackets() {
        auto now = std::chrono::steady_clock::now();

        for (auto& [seqNbr, reliablePkt] : _reliablePackets) {
            auto timeSinceLastSend = std::chrono::duration_cast<std::chrono::milliseconds>(
                now - reliablePkt.lastSentTime
                ).count();

            if (timeSinceLastSend > cmn::ticksBeforeResending) {
                if (reliablePkt.retryCount < cmn::reliabilityRetries) {
                    sendUdp(reliablePkt.packet);
                    reliablePkt.lastSentTime = now;
                    reliablePkt.retryCount++;
                } else {
                    _reliablePackets.erase(seqNbr);
                }
            }
        }
    }

    bool Client::_shouldProcessPacket(const cmn::packetHeader& header, cmn::clientNetworkState state)
    {
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

    void Client::_handleUdpReception(cmn::packetHeader header, cmn::packetData data)
    {
        if (!_shouldProcessPacket(header, _serverState)) {
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

    void Client::_sendAckPacket(cmn::packetHeader header)
    {
        if (!header.isReliable) {
            return;
        }
        cmn::acknowledgeData data = {header.sequenceNbr};
        sendUdp(cmn::PacketFactory::createPacket(data, _reliablePackets));
    }


    int Client::run()
    {
        _tcpThread = std::jthread{[this]{ _handleTcp(); }};

        std::optional sender = sf::IpAddress::LocalHost;
        unsigned short port = 0;
        cmn::CustomPacket packet {};

        while (true) {
            auto receivedData = _sharedData->getUdpPacketToSend();
            if (receivedData.has_value()) {
                sendUdp(cmn::PacketFactory::createPacket(receivedData.value(), _reliablePackets));
            }
            if (_udpSocket.receive(packet, sender, port) != sf::Socket::Status::Done) {
                continue;
            }
            auto data = cmn::PacketDisassembler::disassemble(packet);
            _sendAckPacket(data.first);
            _handleUdpReception(data.first, data.second);
        }
    }
}