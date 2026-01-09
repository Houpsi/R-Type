/*
** EPITECH PROJECT, 2025
** R_Type
** File description:
** Client
*/

#include "Client.hpp"

#include "custom_packet/CustomPacket.hpp"

#include <cstdint>
#include <iostream>
#include <SFML/Network/TcpSocket.hpp>
#include <SFML/Network/IpAddress.hpp>

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

    int Client::sendTcp(const cmn::packetData& dataPacket)
    {
        cmn::CustomPacket packet;
        packet << dataPacket;

        if (_tcpSocket.send(packet) != sf::Socket::Status::Done) {
            std::cerr << "[ERROR]: Failed to send TCP packet.\n";
            return 1;
        }
        //std::cout << "[SEND]: TCP Packet send" << "\n";
        return 0;
    }

    int Client::sendUdp(cmn::CustomPacket &packet)
    {
        if (_udpSocket.send(packet, _serverIp, _serverUdpPort) != sf::Socket::Status::Done) {
            std::cerr << "[ERROR]: Failed to send UDP packet.\n";
            return 1;
        }
        //std::cout << "[SEND]: UDP Packet send" << "\n";
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
                cmn::packetData data;
                packet >> data;
                _sharedData->addTcpReceivedPacket(data);
                //std::cout << "[RECEIVED]: TCP Packet received\n";
            }
        }
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
                sendUdp(receivedData.value());
            }
            if (_udpSocket.receive(packet, sender, port) != sf::Socket::Status::Done) {
//                std::cerr << "[ERROR]: failed to receive UDP packet" << "\n";
                continue;
            }
            cmn::packetData data;
            packet >> data;
            _sharedData->addUdpReceivedPacket(data);
            //std::cout << "[RECEIVED]: UDP Packet received" << "\n";
        }
    }
}