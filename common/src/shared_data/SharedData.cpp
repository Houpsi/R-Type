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

namespace cmn {

    /**
     * @brief Adds a packet to the received queue using a lock_guard for synchronization.
     * @param data The packet to add.
     */
    void SharedData::addReceivedPacket(const packetData &data)
    {
        std::lock_guard const lock(_mutex);
        _receivedQueue.push(data);
    }

    /**
     * @brief Retrieves the next packet from the received queue using a lock_guard.
     * @return The packet if the queue is not empty, otherwise std::nullopt.
     */
    std::optional<packetData> SharedData::getReceivedPacket()
    {
        std::lock_guard const lock(_mutex);
        if (_receivedQueue.empty()) {
            return std::nullopt;
        }
        packetData packetData = _receivedQueue.front();
        _receivedQueue.pop();
        return packetData;
    }

    /**
     * @brief Adds a packet to the send queue using a lock_guard.
     * @param data The packet to add.
     */
    void SharedData::addSendPacket(const packetData &data)
    {
        std::lock_guard const lock(_mutex);
        _sendQueue.push(data);
    }

    /**
     * @brief Retrieves the next packet from the send queue using a lock_guard.
     * @return The packet if the queue is not empty, otherwise std::nullopt.
     */
    std::optional<packetData> SharedData::getSendPacket()
    {
        std::lock_guard const lock(_mutex);
        if (_sendQueue.empty()) {
            return std::nullopt;
        }
        packetData packetData = _sendQueue.front();
        _sendQueue.pop();
        return packetData;
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
}