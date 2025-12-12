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

    int Client::bindPorts(uint16_t port)
    {
        _udpSocket.setBlocking(true);
        if (_udpSocket.bind(port) != sf::Socket::Status::Done) {
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
        if (_socket.connect(ipAddress.value(), port) != sf::Socket::Status::Done) {
            std::cerr << "[ERROR]: Failed to connect to host via TCP.\n";
            return 1;
        }
        _serverIp = ipAddress.value();
        _serverUdpPort = port;
        std::cout << "[CONNECTION]: TCP connection established.\n";
        return 0;
    }

    int Client::run()
    {
        std::optional<sf::IpAddress> sender;
        unsigned short port = 0;
        cmn::CustomPacket packet;

        while (true) {
            if (_udpSocket.receive(packet, sender, port) != sf::Socket::Status::Done) {
                std::cerr << "[ERROR]: failed to receive UDP packet" << "\n";
                continue;
            }
            std::cout << "[RECEIVED]: UDP Packet received" << "\n";
        }
    }
}