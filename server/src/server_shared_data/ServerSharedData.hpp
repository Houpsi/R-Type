/*
** EPITECH PROJECT, 2026
** R_Type
** File description:
** ServerSharedData
*/

#ifndef R_TYPE_SERVERSHAREDDATA_HPP
#define R_TYPE_SERVERSHAREDDATA_HPP

#include "SFML/Network/IpAddress.hpp"
#include "custom_packet/CustomPacket.hpp"
#include "packet_data/PacketData.hpp"

#include <list>
#include <map>
#include <mutex>
#include <queue>
#include <unordered_map>


namespace server {

    class ServerSharedData {
    public:

        void addPlayer(int playerId, int port, const sf::IpAddress &ipAddress);
        void deletePlayer(int port, const sf::IpAddress &ipAddress);
        std::optional<std::pair<int, sf::IpAddress>> getPlayer(int playerId);
        std::vector<int> getAllPlayerIds();
        size_t getPlayerListSize();


        void createLobby(int lobbyId);
        void deleteLobby(int lobbyId);
        void addPlayerToLobby(int playerId, int lobbyId);
        void removePlayerFromLobby(int playerId, int lobbyId);
        std::vector<int> getLobbyPlayers(int lobbyId);
        int getNumberPlayerLobby(int lobbyId);
        int getPlayerLobby(int playerId);
        std::vector<int> getAllLobbyIds();
        std::unordered_map<int, std::pair<int, sf::IpAddress>> getMapPlayers();

        void addSystemPacket(const cmn::packetData &data);
        std::optional<cmn::packetData> getSystemPacket();
        void addLobbyUdpReceivedPacket(int lobbyId, const cmn::packetData &data);
        std::optional<cmn::packetData> getLobbyUdpReceivedPacket(int lobbyId);
        void addLobbyUdpPacketToSend(int lobbyId, const cmn::CustomPacket &packet);
        std::optional<cmn::CustomPacket> getLobbyUdpPacketToSend(int lobbyId);
        void addLobbyTcpReceivedPacket(int lobbyId, const cmn::packetData &data);
        std::optional<cmn::packetData> getLobbyTcpReceivedPacket(int lobbyId);
        void addLobbyTcpPacketToSend(int lobbyId, const cmn::CustomPacket &packet);
        std::optional<cmn::CustomPacket> getLobbyTcpPacketToSend(int lobbyId);

    private:
        std::unordered_map<int, std::pair<int, sf::IpAddress>> _playerList;
        std::unordered_map<int, int> _playerLobbyMap;
        std::map<int, std::list<int>> _lobbyPlayers;

        std::map<int, std::queue<cmn::packetData>> _lobbyUdpReceivedQueues;
        std::map<int, std::queue<cmn::CustomPacket>> _lobbyUdpSendQueues;
        std::map<int, std::queue<cmn::packetData>> _lobbyTcpReceivedQueues;
        std::map<int, std::queue<cmn::CustomPacket>> _lobbyTcpSendQueues;
        std::queue<cmn::packetData> _systemPacketQueue;

        std::mutex _mutex;
    };
}

#endif// R_TYPE_SERVERSHAREDDATA_HPP
