/*
** EPITECH PROJECT, 2025
** R_Type
** File description:
** Server
*/
#include "Server.hpp"
#include "SFML/Network/Packet.hpp"
#include "SFML/Network/TcpSocket.hpp"
#include <iostream>
#include <thread>

namespace server {

    int Server::bindPorts(uint16_t port)
    {
        _listener.setBlocking(false);
        _udpSocket.setBlocking(true);
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
                sf::Packet packet;
                if (sock.receive(packet) != sf::Socket::Status::Done) {
                    std::cerr << "[ERROR]: failed to receive TCP packet" << "\n";
                    return;
                }
                // TODO -> handle received UDP packet
                std::cout << "[RECEIVED]: TCP Packet received" << "\n";
            }
        }
    }

    void Server::run()
    {
        _socketSelector.add(_listener);

        _tcpThread = std::jthread{[this]{ _handleTcp(); }};

        while (true) {
            std::optional<sf::IpAddress> sender;
            unsigned short port = 0;
            sf::Packet packet;
            if (_udpSocket.receive(packet, sender, port) != sf::Socket::Status::Done) {
                std::cerr << "[ERROR]: failed to receive UDP packet" << "\n";
                continue;
            }
            // TODO -> handle received UDP packet
            std::cout << "[RECEIVED]: UDP Packet received" << "\n";
        }
    }

    void Server::_acceptConnection()
    {
        auto client = std::make_unique<sf::TcpSocket>();

        client->setBlocking(false);

        if (_listener.accept(*client) != sf::Socket::Status::Done) {
            std::cerr << "[ERROR]: failed to accept new TCP connection" << "\n";
            return;
        }
        _socketSelector.add(*client);
        _socketVector.push_back(std::move(client));
        std::cout << "[CONNECTION]: TCP connection accepted" << "\n";
    }

}// namespace server