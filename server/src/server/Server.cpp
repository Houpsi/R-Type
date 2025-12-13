/*
** EPITECH PROJECT, 2025
** R_Type
** File description:
** Server
*/
#include "Server.hpp"

#include "custom_packet/CustomPacket.hpp"
#include "SFML/Network/TcpSocket.hpp"
#include <iostream>
#include <thread>

namespace server {
     Server::Server(const std::shared_ptr<cmn::SharedData> &data):
    _sharedData(data) {}


    int Server::bindPorts(const uint16_t port)
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
                cmn::CustomPacket packet;
                sf::Socket::Status const status = sock.receive(packet);
                if (status != sf::Socket::Status::Done) {
                    std::cerr << "[ERROR]: failed to receive TCP packet" << "\n";
                    if (status == sf::Socket::Status::Disconnected || status == sf::Socket::Status::Error) {
                        std::cout << "[DISCONNECTION]: Client " << sock.getRemoteAddress().value() << ":" << sock.getRemotePort() << " disconnected." << "\n";
                        _socketSelector.remove(sock);
                        it = _socketVector.erase(it);
                        _sharedData->deletePlayer(sock.getRemotePort(), sock.getRemoteAddress().value());
                    }
                }
                // TODO -> handle received UDP packet
                std::cout << "[RECEIVED]: TCP Packet received" << "\n";
            }
        }
    }

    int Server::sendUdp(const cmn::packetData& packet, const sf::IpAddress& clientIp, uint16_t port)
    {
        cmn::CustomPacket custom_packet;
        custom_packet << packet;

        sf::Socket::Status const status = _udpSocket.send(custom_packet, clientIp, port);
        if (status != sf::Socket::Status::Done) {
            std::cerr << "[ERROR]: failed to send UDP packet to:"
            << clientIp << ":" << port << "\n";
            return 1;
        }
        return 0;
    }

    int Server::sendTcp(const cmn::packetData& packet, sf::TcpSocket& clientSocket)
    {
        cmn::CustomPacket custom_packet;
        custom_packet << packet;

        sf::Socket::Status const status = clientSocket.send(custom_packet);
        if (status != sf::Socket::Status::Done) {
            std::cerr << "[ERROR]: failed to send TCP packet to server" << "\n";
            return 1;
        }
        return 0;
    }

    int Server::broadcastTcp(const cmn::packetData& packet) const
    {
        for (const auto &client : _socketVector) {
            if (sendTcp(packet, *client) == 1) {
                return 1;
            }
        }
        return 0;
    }

    int Server::broadcastUdp(const cmn::packetData& packet, uint16_t port)
    {
        for (const auto &client : _socketVector) {
            auto ip = client->getRemoteAddress();
            if (!ip.has_value()) {
                continue;
            }
            if (sendUdp(packet, ip.value(), port) == 1) {
                return 1;
            }
        }
        return 0;
    }

    void Server::_acceptConnection()
    {
        static int idPlayer = 0;
        auto client = std::make_unique<sf::TcpSocket>();

        client->setBlocking(false);

        if (_listener.accept(*client) != sf::Socket::Status::Done) {
            std::cerr << "[ERROR]: failed to accept new TCP connection" << "\n";
            return;
        }
        _socketSelector.add(*client);
        _socketVector.push_back(std::move(client));
        _sharedData->addPlayer(idPlayer, client->getRemotePort(), client->getRemoteAddress().value());
        std::cout << "[CONNECTION]: TCP connection accepted" << "\n";
        idPlayer++;
    }

    void Server::run()
    {
        _socketSelector.add(_listener);

        _tcpThread = std::jthread{[this]{ _handleTcp(); }};

        std::optional<sf::IpAddress> sender;
        unsigned short port = 0;
        cmn::CustomPacket packet;

        while (true) {
            if (_udpSocket.receive(packet, sender, port) != sf::Socket::Status::Done) {
                std::cerr << "[ERROR]: failed to receive UDP packet" << "\n";
                continue;
            }
            // TODO -> handle received UDP packet
            std::cout << "[RECEIVED]: UDP Packet received" << "\n";
        }
    }

}// namespace server