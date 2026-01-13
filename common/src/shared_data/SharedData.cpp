/*
** EPITECH PROJECT, 2025
** R_Type
** File description:
** SharedData
*/

/**
 * @file SharedData.cpp
 * @brief Implementation of the methods for the server::SharedData class.
*/

#include "SharedData.hpp"
#include <iostream>

namespace cmn {

    /**
     * @brief Adds a packet to the received queue using a lock_guard for synchronization.
     * @param data The packet to add.
     */
    void SharedData::addUdpReceivedPacket(const packetData &data)
    {
        std::lock_guard const lock(_mutex);
//        std::cout << _udpReceivedQueue.size() << "\n";
        _udpReceivedQueue.push(data);
    }

    /**
     * @brief Retrieves the next packet from the received queue using a lock_guard.
     * @return The packet if the queue is not empty, otherwise std::nullopt.
     */
    std::optional<packetData> SharedData::getUdpReceivedPacket()
    {
        std::lock_guard const lock(_mutex);
        if (_udpReceivedQueue.empty()) {
            return std::nullopt;
        }
        packetData packetData = _udpReceivedQueue.front();
        _udpReceivedQueue.pop();
        return packetData;
    }

    /**
     * @brief Adds a packet to the send queue using a lock_guard.
     * @param data The packet to add.
     */
    void SharedData::addUdpPacketToSend(const CustomPacket &packet)
    {
        std::lock_guard const lock(_mutex);
        _udpSendQueue.push(packet);
    }

    /**
     * @brief Retrieves the next packet from the send queue using a lock_guard.
     * @return The packet if the queue is not empty, otherwise std::nullopt.
     */
    std::optional<CustomPacket> SharedData::getUdpPacketToSend()
    {
        std::lock_guard const lock(_mutex);
        if (_udpSendQueue.empty()) {
            return std::nullopt;
        }
        CustomPacket packet = _udpSendQueue.front();
        _udpSendQueue.pop();
        return packet;
    }

    /**
     * @brief Adds a packet to the received queue using a lock_guard for synchronization.
     * @param data The packet to add.
     */
    void SharedData::addTcpReceivedPacket(const packetData &data)
    {
        std::lock_guard const lock(_mutex);
        _tcpReceivedQueue.push(data);
    }

    /**
     * @brief Retrieves the next packet from the received queue using a lock_guard.
     * @return The packet if the queue is not empty, otherwise std::nullopt.
     */
    std::optional<packetData> SharedData::getTcpReceivedPacket()
    {
        std::lock_guard const lock(_mutex);
        if (_tcpReceivedQueue.empty()) {
            return std::nullopt;
        }
        packetData packetData = _tcpReceivedQueue.front();
        _tcpReceivedQueue.pop();
        return packetData;
    }

    /**
     * @brief Adds a packet to the send queue using a lock_guard.
     * @param data The packet to add.
     */
    void SharedData::addTcpPacketToSend(const CustomPacket &packet)
    {
        std::lock_guard const lock(_mutex);
        _tcpSendQueue.push(packet);
    }

    /**
     * @brief Retrieves the next packet from the send queue using a lock_guard.
     * @return The packet if the queue is not empty, otherwise std::nullopt.
     */
    std::optional<CustomPacket> SharedData::getTcpPacketToSend()
    {
        std::lock_guard const lock(_mutex);
        if (_tcpSendQueue.empty()) {
            return std::nullopt;
        }
        CustomPacket packet = _tcpSendQueue.front();
        _tcpSendQueue.pop();
        return packet;
    }

    /**
     * @brief Adds a player's information to the list using a lock_guard.
     * @param playerId The player's identifier.
     * @param port The connection port.
     * @param ipAddress The IP address.
     */
    void SharedData::addPlayer(int playerId, int port, const sf::IpAddress &ipAddress)
    {
        const std::lock_guard lock(_mutex);
        _playerList.emplace(playerId, std::make_pair(port, ipAddress));
    }

    void SharedData::deletePlayer(int port, const sf::IpAddress &ipAddress)
    {
        int playerPort = 0;
        sf::IpAddress playerAddress = sf::IpAddress::LocalHost;

        for (auto it = _playerList.begin(); it != _playerList.end(); ) {
            playerPort = it->second.first;
            playerAddress = it->second.second;

            if (playerPort == port && playerAddress == ipAddress) {
                it = _playerList.erase(it);
            } else {
                ++it;
            }
        }
    }

     /**
     * @brief Retrieves a player's information by their ID using a lock_guard.
     * @param playerId The player's identifier.
     * @return A pair (port, IP address) if the player is found, otherwise std::nullopt.
     */
     std::optional<std::pair<int, sf::IpAddress>> SharedData::getPlayer(const int playerId)
    {
        const std::lock_guard lock(_mutex);
        if (!_playerList.contains(playerId)) {
            return std::nullopt;
        }
        return _playerList.at(playerId);
    }

    size_t SharedData::getPlayerListSize()
    {
        const std::lock_guard lock(_mutex);
        return _playerList.size();
    }

    std::vector<int> SharedData::getAllPlayerIds()
    {
        const std::lock_guard lock(_mutex);
        std::vector<int> ids;

        for (auto &it : _playerList) {
            ids.push_back(it.first);
        }
        return ids;
    }

    void SharedData::deleteLobby(const int lobbyId)
    {
        const std::lock_guard lock(_mutex);

        const auto it = _mapLobbiesPlayers.find(lobbyId);
        if (it == _mapLobbiesPlayers.end()) {
            std::cout << "Trying to delete invalid lobbyId in player map" << "\n";
        }
        _mapLobbiesPlayers.erase(it);
        const auto itReceived = _mapLobbiesPacketListReceived.find(lobbyId);
        if (itReceived == _mapLobbiesPacketListReceived.end()) {
            std::cout << "Trying to delete invalid lobbyId in received map" << "\n";
        }
        _mapLobbiesPacketListSend.erase(itReceived);
        const auto itSend = _mapLobbiesPacketListSend.find(lobbyId);
        if (itSend == _mapLobbiesPacketListSend.end()) {
            std::cout << "Trying to delete invalid lobbyId in send map" << "\n";
        }
        _mapLobbiesPacketListSend.erase(itSend);
    }

    void SharedData::addPlayerToLobby(int playerId, int lobbyId)
    {
        const std::lock_guard lock(_mutex);
        _mapLobbiesPlayers[lobbyId].emplace_back(playerId);
    }

    void SharedData::deletePlayerToLobby(int playerId, int lobbyId)
    {
        const std::lock_guard lock(_mutex);
        auto it = _mapLobbiesPlayers.find(lobbyId);
        if (it == _mapLobbiesPlayers.end()) {
            std::cout << "Trying to delete player in invalid lobbyId" << "\n";
        }
        _mapLobbiesPlayers[lobbyId].remove(playerId);
    }

    void SharedData::addMessageUDPToSend(int lobbyId, const CustomPacket &message)
    {
        const std::lock_guard lock(_mutex);
        _mapLobbiesPacketListReceived[lobbyId].push(message);
    }

    std::optional<CustomPacket> SharedData::getMessageUDPToSend(int lobbyId)
    {
        const std::lock_guard lock(_mutex);
        if (_mapLobbiesPacketListReceived[lobbyId].empty()) {
            return std::nullopt;
        }

        auto packet = _mapLobbiesPacketListSend[lobbyId].front();
        _mapLobbiesPacketListSend[lobbyId].pop();
        return packet;
    }

    int SharedData::getNumberPlayerLobby(const int id)
    {
        const std::lock_guard lock(_mutex);
        return static_cast<int>(_mapLobbiesPlayers[id].size());
    }

}
