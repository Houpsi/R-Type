/*
** EPITECH PROJECT, 2026
** R_Type
** File description:
** LobbyManager
*/

#include "LobbyManager.hpp"

#include "Constants.hpp"
#include "game/Game.hpp"
#include "packet_factory/PacketFactory.hpp"

#include <iostream>

namespace server {

     LobbyManager::LobbyManager(const std::shared_ptr<ServerSharedData> &sharedData)
        : _sharedData(sharedData), _lastPlayerCount(0)
    {}

    LobbyManager::~LobbyManager()
     {
         _activeGames.clear();
     }

    void LobbyManager::run()
     {
         while (true) {
             auto packet = _sharedData->getSystemPacket();
             if (packet.has_value()) {
                 _getPacketType(packet.value());
             }
             _handleMatchMaking();
             _handlePlayerDisconnections();
             _cleanupFinishedGames();
             std::this_thread::sleep_for(std::chrono::milliseconds(10));
         }
     }

    int LobbyManager::_getPacketType(cmn::packetData &data)
    {
        std::visit([this](auto &&arg) {
            using T = std::decay_t<decltype(arg)>;

            if constexpr (std::is_same_v<T, packetSoloGame>) {
                packetSoloGame &solo = arg;
                Lobby newLobby = _createLobby(cmn::LobbyType::Solo);
                _lobbyMap[newLobby.id] = newLobby;
                _sharedData->createLobby(newLobby.id);
                _sharedData->addPlayerToLobby(solo.playerId, newLobby.id);
                // TODO: send player the lobby id
                _launchGame(newLobby.id);
            } else if constexpr (std::is_same_v<T, packetCreateLobby>) {
                packetCreateLobby &createLobby = arg;
                Lobby newLobby = _createLobby(cmn::LobbyType::Lobby);
                newLobby.code = _createLobbyCode();
                _lobbyMap[newLobby.id] = newLobby;
                _sharedData->createLobby(newLobby.id);
                _sharedData->addPlayerToLobby(createLobby.playerId, newLobby.id);
                // TODO: send player the lobby id
                auto codePacket = cmn::PacketFactory::createLobbyCodePacket(newLobby.code);
                _sharedData->addLobbyTcpPacketToSend(newLobby.id, codePacket);
            } else if constexpr (std::is_same_v<T, packetJoinLobby>) {
                packetJoinLobby &joinLobby = arg;
                _joinLobby(joinLobby.code, joinLobby.playerId);
            } else if constexpr (std::is_same_v<T, packetMatchMaking>) {
                packetMatchMaking &matchmaking = arg;
                if (_playersInMatchmaking.find(matchmaking.playerId) == _playersInMatchmaking.end()) {
                    _matchmakingQueue.push(matchmaking.playerId);
                    _playersInMatchmaking.insert(matchmaking.playerId);
                }
            } else if constexpr (std::is_same_v<T, packetLeaveLobby>) {
                packetLeaveLobby &leaveLobby = arg;
                _leaveLobby(leaveLobby.playerId);
            }
        }, data.content);

        return 0;
    }

    Lobby LobbyManager::_createLobby(const cmn::LobbyType lobbyType)
     {
         static int index = 0;
         Lobby lobby;
         lobby.id = index++;
         lobby.type = lobbyType;
         lobby.state = cmn::LobbyState::Waiting;
         lobby.createdAt = std::chrono::steady_clock::now();
         return lobby;
     }

     void LobbyManager::_handleMatchMaking()
    {
        while (_matchmakingQueue.size() >= cmn::max_players) {
            Lobby newLobby = _createLobby(cmn::LobbyType::Matchmaking);
            _lobbyMap[newLobby.id] = newLobby;
            _sharedData->createLobby(newLobby.id);

            for (uint8_t i = 0; i < cmn::max_players; ++i) {
                int playerId = _matchmakingQueue.front();
                _matchmakingQueue.pop();
                _playersInMatchmaking.erase(playerId);
                _sharedData->addPlayerToLobby(playerId, newLobby.id);
            }

            _launchGame(newLobby.id);
        }
    }

    void LobbyManager::_joinLobby(const std::string &code, const int playerId)
     {
         Lobby* lobby = _findLobbyByCode(code);

         // TODO: Send to specific player
         if (!lobby) {
             auto errorPacket = cmn::PacketFactory::createErrorPacket("Lobby not found");
             return;
         }

         if (lobby->state != cmn::LobbyState::Waiting) {
             auto errorPacket = cmn::PacketFactory::createErrorPacket("Game already started");
             return;
         }

         int currentPlayers = _sharedData->getNumberPlayerLobby(lobby->id);
         if (currentPlayers >= cmn::max_players) {
             auto errorPacket = cmn::PacketFactory::createErrorPacket("Lobby is full");
             return;
         }

         _sharedData->addPlayerToLobby(playerId, lobby->id);
         auto successPacket = cmn::PacketFactory::createJoinSuccessPacket(lobby->id);
         _sharedData->addLobbyTcpPacketToSend(lobby->id, successPacket);
         if (currentPlayers + 1 >= cmn::max_players) {
             _launchGame(lobby->id);
         }
     }

    void LobbyManager::_leaveLobby(const int playerId)
     {
         int lobbyId = _sharedData->getPlayerLobby(playerId);

         if (lobbyId == -1) {
             return;
         }
         _sharedData->removePlayerFromLobby(playerId, lobbyId);
         if (_sharedData->getNumberPlayerLobby(lobbyId) == 0) {
             _lobbyMap.erase(lobbyId);
             _sharedData->deleteLobby(lobbyId);
             if (_activeGames.contains(lobbyId)) {
                 _activeGames.erase(lobbyId);
             }
         }
     }

    void LobbyManager::_handlePlayerDisconnections()
    {
        size_t currentPlayerCount = _sharedData->getPlayerListSize();

        if (currentPlayerCount < _lastPlayerCount) {
            std::vector<int> allPlayerIds = _sharedData->getAllPlayerIds();

            std::queue<int> newMatchmakingQueue;
            while (!_matchmakingQueue.empty()) {
                int playerId = _matchmakingQueue.front();
                _matchmakingQueue.pop();
                if (std::ranges::find(allPlayerIds, playerId) != allPlayerIds.end()) {
                    newMatchmakingQueue.push(playerId);
                } else {
                    _playersInMatchmaking.erase(playerId);
                }
            }
            _matchmakingQueue = std::move(newMatchmakingQueue);

            for (auto it = _lobbyMap.begin(); it != _lobbyMap.end(); ) {
                int lobbyId = it->first;
                std::vector<int> lobbyPlayers = _sharedData->getLobbyPlayers(lobbyId);

                for (int playerId : lobbyPlayers) {
                    if (std::ranges::find(allPlayerIds, playerId) == allPlayerIds.end()) {
                        _sharedData->removePlayerFromLobby(playerId, lobbyId);
                    }
                }
                if (_sharedData->getNumberPlayerLobby(lobbyId) == 0) {
                    _sharedData->deleteLobby(lobbyId);
                    if (_activeGames.contains(lobbyId)) {
                        _activeGames.erase(lobbyId);
                    }
                    it = _lobbyMap.erase(it);
                } else {
                    ++it;
                }
            }
        }

        _lastPlayerCount = currentPlayerCount;
    }

    void LobbyManager::_launchGame(int lobbyId)
    {
        if (_activeGames.contains(lobbyId)) {
            return;
        }

        _lobbyMap[lobbyId].state = cmn::LobbyState::Running;

        _activeGames[lobbyId] = std::jthread([this, lobbyId]() {
            try {
                Game game(_sharedData, lobbyId, _lobbyMap[lobbyId].type);
                game.run();
            } catch (const std::exception &e) {
                std::cerr << "Game error in lobby " << lobbyId << ": " << e.what() << "\n";
            }
            _lobbyMap[lobbyId].state = cmn::LobbyState::EndGame;
        });
    }

    void LobbyManager::_cleanupFinishedGames()
    {
        for (auto it = _lobbyMap.begin(); it != _lobbyMap.end(); ) {
            if (it->second.state == cmn::LobbyState::EndGame) {
                int lobbyId = it->first;
                if (_activeGames.contains(lobbyId)) {
                    _activeGames.erase(lobbyId);
                }
                _sharedData->deleteLobby(lobbyId);
                it = _lobbyMap.erase(it);
            } else {
                ++it;
            }
        }
    }

    std::string LobbyManager::_createLobbyCode()
    {
        return std::to_string(rand() % 900000 + 100000);
    }

    Lobby* LobbyManager::_findLobbyByCode(const std::string &code)
    {
        for (auto &[lobbyId, lobby] : _lobbyMap) {
            if (lobby.type == cmn::LobbyType::Lobby && lobby.code == code) {
                return &lobby;
            }
        }
        return nullptr;
    }

}