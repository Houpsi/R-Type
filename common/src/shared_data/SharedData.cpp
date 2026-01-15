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
    void SharedData::addUdpReceivedPacket(const CustomPacket &packet)
    {
        std::lock_guard const lock(_mutex);
//        std::cout << _udpReceivedQueue.size() << "\n";
        _udpReceivedQueue.push(packet);
    }

    /**
     * @brief Retrieves the next packet from the received queue using a lock_guard.
     * @return The packet if the queue is not empty, otherwise std::nullopt.
     */
    std::optional<CustomPacket> SharedData::getUdpReceivedPacket()
    {
        std::lock_guard const lock(_mutex);
        if (_udpReceivedQueue.empty()) {
            return std::nullopt;
        }
        CustomPacket packet = _udpReceivedQueue.front();
        _udpReceivedQueue.pop();
        return packet;
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
    void SharedData::addTcpReceivedPacket(const CustomPacket &packet)
    {
        std::lock_guard const lock(_mutex);
        _tcpReceivedQueue.push(packet);
    }

    /**
     * @brief Retrieves the next packet from the received queue using a lock_guard.
     * @return The packet if the queue is not empty, otherwise std::nullopt.
     */
    std::optional<CustomPacket> SharedData::getTcpReceivedPacket()
    {
        std::lock_guard const lock(_mutex);
        if (_tcpReceivedQueue.empty()) {
            return std::nullopt;
        }
        CustomPacket packet = _tcpReceivedQueue.front();
        _tcpReceivedQueue.pop();
        return packet;
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

    bool SharedData::getRunThread()
    {
        const std::lock_guard lock(_mutex);
        return _isRunning;
    }

    void SharedData::setRunThread(bool run)
    {
        std::lock_guard const lock(_mutex);
        _isRunning = run;
    }
}// namespace cmn