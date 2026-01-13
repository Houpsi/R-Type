/*
** EPITECH PROJECT, 2026
** R_Type
** File description:
** ServerSharedData
*/

#include "ServerSharedData.hpp"
#include <algorithm>
#include <iostream>

namespace server {

    void ServerSharedData::addPlayer(int playerId, int port, const sf::IpAddress &ipAddress)
    {
        std::lock_guard const lock(_mutex);
        _playerList.emplace(playerId, std::make_pair(port, ipAddress));
    }

    void ServerSharedData::deletePlayer(int port, const sf::IpAddress &ipAddress)
    {
        std::lock_guard const lock(_mutex);
        
        for (auto it = _playerList.begin(); it != _playerList.end(); ) {
            if (it->second.first == port && it->second.second == ipAddress) {
                if (int const playerId = it->first; _playerLobbyMap.contains(playerId)) {
                    int const lobbyId = _playerLobbyMap[playerId];
                    _lobbyPlayers[lobbyId].remove(playerId);
                    _playerLobbyMap.erase(playerId);
                }
                it = _playerList.erase(it);
            } else {
                ++it;
            }
        }
    }

    std::optional<std::pair<int, sf::IpAddress>> ServerSharedData::getPlayer(const int playerId)
    {
        std::lock_guard const lock(_mutex);
        if (!_playerList.contains(playerId)) {
            return std::nullopt;
        }
        return _playerList.at(playerId);
    }

    std::vector<int> ServerSharedData::getAllPlayerIds()
    {
        std::lock_guard const lock(_mutex);
        std::vector<int> ids;
        for (auto &[id, _] : _playerList) {
            ids.push_back(id);
        }
        return ids;
    }

    std::unordered_map<int, std::pair<int, sf::IpAddress>> ServerSharedData::getMapPlayers()
    {
        std::lock_guard const lock(_mutex);
        return _playerList;
    }


    size_t ServerSharedData::getPlayerListSize()
    {
        std::lock_guard const lock(_mutex);
        return _playerList.size();
    }
    
    void ServerSharedData::createLobby(int lobbyId)
    {
        std::lock_guard const lock(_mutex);
        _lobbyPlayers[lobbyId] = std::list<int>();
        _lobbyUdpReceivedQueues[lobbyId] = std::queue<cmn::packetData>();
        _lobbyUdpSendQueues[lobbyId] = std::queue<cmn::CustomPacket>();
        _lobbyTcpReceivedQueues[lobbyId] = std::queue<cmn::packetData>();
        _lobbyTcpSendQueues[lobbyId] = std::queue<cmn::CustomPacket>();
    }

    void ServerSharedData::deleteLobby(int lobbyId)
    {
        std::lock_guard const lock(_mutex);
        
        if (_lobbyPlayers.contains(lobbyId)) {
            for (int playerId : _lobbyPlayers[lobbyId]) {
                _playerLobbyMap.erase(playerId);
            }
        }
        _lobbyPlayers.erase(lobbyId);
        _lobbyUdpReceivedQueues.erase(lobbyId);
        _lobbyUdpSendQueues.erase(lobbyId);
        _lobbyTcpReceivedQueues.erase(lobbyId);
        _lobbyTcpSendQueues.erase(lobbyId);
    }

    void ServerSharedData::addPlayerToLobby(int playerId, int lobbyId)
    {
        std::lock_guard const lock(_mutex);
        
        if (_playerLobbyMap.contains(playerId)) {
            const int oldLobby = _playerLobbyMap[playerId];
            _lobbyPlayers[oldLobby].remove(playerId);
        }
        _lobbyPlayers[lobbyId].push_back(playerId);
        _playerLobbyMap[playerId] = lobbyId;
    }

    void ServerSharedData::removePlayerFromLobby(int playerId, int lobbyId)
    {
        std::lock_guard const lock(_mutex);
        
        if (_lobbyPlayers.contains(lobbyId)) {
            _lobbyPlayers[lobbyId].remove(playerId);
        }
        if (_playerLobbyMap.contains(playerId) && _playerLobbyMap[playerId] == lobbyId) {
            _playerLobbyMap.erase(playerId);
        }
    }

    std::vector<int> ServerSharedData::getLobbyPlayers(int lobbyId)
    {
        std::lock_guard const lock(_mutex);
        
        if (!_lobbyPlayers.contains(lobbyId)) {
            return {};
        }
        return {_lobbyPlayers[lobbyId].begin(), _lobbyPlayers[lobbyId].end()};
    }

    int ServerSharedData::getNumberPlayerLobby(int lobbyId)
    {
        std::lock_guard const lock(_mutex);
        
        if (!_lobbyPlayers.contains(lobbyId)) {
            return 0;
        }
        return static_cast<int>(_lobbyPlayers[lobbyId].size());
    }

    int ServerSharedData::getPlayerLobby(int playerId)
    {
        std::lock_guard const lock(_mutex);
        
        if (!_playerLobbyMap.contains(playerId)) {
            return -1;
        }
        return _playerLobbyMap[playerId];
    }

    std::vector<int> ServerSharedData::getAllLobbyIds()
    {
        std::lock_guard const lock(_mutex);
        std::vector<int> lobbyIds;
        
        for (const auto &[lobbyId, _] : _lobbyPlayers) {
            lobbyIds.push_back(lobbyId);
        }
        return lobbyIds;
    }

    void ServerSharedData::addSystemPacket(const cmn::packetData &data)
    {
        std::lock_guard const lock(_mutex);
        _systemPacketQueue.push(data);
    }

    std::optional<cmn::packetData> ServerSharedData::getSystemPacket()
    {
        std::lock_guard const lock(_mutex);
        
        if (_systemPacketQueue.empty()) {
            return std::nullopt;
        }
        cmn::packetData data = _systemPacketQueue.front();
        _systemPacketQueue.pop();
        return data;
    }


    void ServerSharedData::addLobbyUdpReceivedPacket(int lobbyId, const cmn::packetData &data)
    {
        std::lock_guard const lock(_mutex);
        
        if (!_lobbyUdpReceivedQueues.contains(lobbyId)) {
            std::cerr << "[ERROR] Trying to add UDP packet to a non-existent lobby" << lobbyId << "\n";
            return;
        }
        _lobbyUdpReceivedQueues[lobbyId].push(data);
    }

    std::optional<cmn::packetData> ServerSharedData::getLobbyUdpReceivedPacket(int lobbyId)
    {
        std::lock_guard const lock(_mutex);
        
        if (!_lobbyUdpReceivedQueues.contains(lobbyId) || _lobbyUdpReceivedQueues[lobbyId].empty()) {
            return std::nullopt;
        }
        cmn::packetData data = _lobbyUdpReceivedQueues[lobbyId].front();
        _lobbyUdpReceivedQueues[lobbyId].pop();
        return data;
    }

    void ServerSharedData::addLobbyUdpPacketToSend(int lobbyId, const cmn::CustomPacket &packet)
    {
        std::lock_guard const lock(_mutex);
        
        if (!_lobbyUdpSendQueues.contains(lobbyId)) {
            std::cerr << "[ERROR] Trying to send UDP packet to a non-existent lobby " << lobbyId << "\n";
            return;
        }
        _lobbyUdpSendQueues[lobbyId].push(packet);
    }

    std::optional<cmn::CustomPacket> ServerSharedData::getLobbyUdpPacketToSend(int lobbyId)
    {
        std::lock_guard const lock(_mutex);
        
        if (!_lobbyUdpSendQueues.contains(lobbyId) || _lobbyUdpSendQueues[lobbyId].empty()) {
            return std::nullopt;
        }
        
        cmn::CustomPacket packet = _lobbyUdpSendQueues[lobbyId].front();
        _lobbyUdpSendQueues[lobbyId].pop();
        return packet;
    }

    void ServerSharedData::addLobbyTcpReceivedPacket(int lobbyId, const cmn::packetData &data)
    {
        std::lock_guard const lock(_mutex);
        
        if (!_lobbyTcpReceivedQueues.contains(lobbyId)) {
            std::cerr << "[ERROR] Trying to add TCP packet to a non-existent lobby " << lobbyId << "\n";
            return;
        }
        _lobbyTcpReceivedQueues[lobbyId].push(data);
    }

    std::optional<cmn::packetData> ServerSharedData::getLobbyTcpReceivedPacket(int lobbyId)
    {
        std::lock_guard const lock(_mutex);
        
        if (!_lobbyTcpReceivedQueues.contains(lobbyId) || _lobbyTcpReceivedQueues[lobbyId].empty()) {
            return std::nullopt;
        }
        cmn::packetData data = _lobbyTcpReceivedQueues[lobbyId].front();
        _lobbyTcpReceivedQueues[lobbyId].pop();
        return data;
    }

    void ServerSharedData::addLobbyTcpPacketToSend(int lobbyId, const cmn::CustomPacket &packet)
    {
        std::lock_guard const lock(_mutex);
        
        if (!_lobbyTcpSendQueues.contains(lobbyId)) {
            std::cerr << "[ERROR] Trying to send TCP packet to a non-existent lobby " << lobbyId << "\n";
            return;
        }
        _lobbyTcpSendQueues[lobbyId].push(packet);
    }

    std::optional<cmn::CustomPacket> ServerSharedData::getLobbyTcpPacketToSend(int lobbyId)
    {
        std::lock_guard const lock(_mutex);
        
        if (!_lobbyTcpSendQueues.contains(lobbyId) || _lobbyTcpSendQueues[lobbyId].empty()) {
            return std::nullopt;
        }
        cmn::CustomPacket packet = _lobbyTcpSendQueues[lobbyId].front();
        _lobbyTcpSendQueues[lobbyId].pop();
        return packet;
    }

}