/*
** EPITECH PROJECT, 2026
** R_Type
** File description:
** LobbyManager
*/

#include "LobbyManager.hpp"
#include "game/Game.hpp"
#include "packet_disassembler/PacketDisassembler.hpp"
#include "packet_factory/PacketFactory.hpp"

#include <iostream>
#include <ranges>

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
             auto data = _sharedData->getSystemPacket();
             if (data.has_value()) {
                 _getPacketType(data.value());
             }
             _handleMatchMaking();
             _handlePlayerDisconnections();
             _cleanupFinishedGames();
             std::this_thread::sleep_for(std::chrono::milliseconds(10));
         }
     }

    void LobbyManager::_getPacketType(cmn::packetData &data)
    {
        std::visit([this](auto &&arg) {
            using T = std::decay_t<decltype(arg)>;
            if constexpr (std::is_same_v<T, cmn::selectModeData>) {
                if (_sharedData->getPlayerLobby(arg.playerId) != -1) {
                    return;
                }
                const cmn::selectModeData &selectModeData = arg;
                _checkModeSelected(selectModeData);
            } else if constexpr (std::is_same_v<T, cmn::requestJoinLobbyData>) {
                if (_sharedData->getPlayerLobby(arg.playerId) != -1) {
                    return;
                }
                const cmn::requestJoinLobbyData &joinLobby = arg;
                _joinLobby(joinLobby.lobbyCode, joinLobby.playerId);
            } else if constexpr (std::is_same_v<T, cmn::leaveLobbyData>) {
                const cmn::leaveLobbyData &leaveLobby = arg;
                _leaveLobby(leaveLobby.playerId);
            }
        }, data);
    }

    void LobbyManager::_checkModeSelected(cmn::selectModeData data)
     {
         if (data.lobbyType == cmn::LobbyType::Solo) {
             Lobby newLobby = _createLobby(cmn::LobbyType::Solo);
             _lobbyMap[newLobby.id] = newLobby;
             _sharedData->createLobby(newLobby.id);
             _sharedData->addPlayerToLobby(data.playerId, newLobby.id);

             cmn::joinLobbyData joinData = {
                 static_cast<uint32_t>(newLobby.id),
                 static_cast<uint8_t>(newLobby.type),
                 static_cast<uint32_t>(newLobby.code)
             };
             _sharedData->addLobbyTcpPacketToSend(newLobby.id, joinData);
             _launchGame(newLobby.id);
         } else if (data.lobbyType == cmn::LobbyType::Lobby) {
             Lobby newLobby = _createLobby(cmn::LobbyType::Lobby);
             newLobby.code = _createLobbyCode();
             _lobbyMap[newLobby.id] = newLobby;
             _sharedData->createLobby(newLobby.id);
             _sharedData->addPlayerToLobby(data.playerId, newLobby.id);
             cmn::joinLobbyData joinData = {
                 static_cast<uint32_t>(newLobby.id),
                 static_cast<uint8_t>(newLobby.type),
                 static_cast<uint32_t>(newLobby.code)
             };
             _sharedData->addLobbyTcpPacketToSend(newLobby.id, joinData);
             _launchGame(newLobby.id);
         } else if (data.lobbyType == cmn::LobbyType::Matchmaking) {
             if (!_playersInMatchmaking.contains(data.playerId)) {
                 _matchmakingQueue.push(data.playerId);
                 _playersInMatchmaking.insert(data.playerId);
             }
         }
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
        while (_matchmakingQueue.size() >= cmn::maxPlayers) {
            Lobby const newLobby = _createLobby(cmn::LobbyType::Matchmaking);
            _lobbyMap[newLobby.id] = newLobby;
            _sharedData->createLobby(newLobby.id);

            for (uint8_t i = 0; i < cmn::maxPlayers; ++i) {
                int const playerId = _matchmakingQueue.front();
                _matchmakingQueue.pop();
                _playersInMatchmaking.erase(playerId);
                _sharedData->addPlayerToLobby(playerId, newLobby.id);
            }

            _launchGame(newLobby.id);
        }
    }

    void LobbyManager::_joinLobby(int code, const int playerId)
     {
         Lobby const* lobby = _findLobbyByCode(code);

         if (lobby == nullptr) {
             cmn::errorTcpData data {0};
             _sharedData->addTcpPacketToSendToSpecificPlayer(playerId, data);
             return;
         }

         if (lobby->state != cmn::LobbyState::Waiting) {
             cmn::errorTcpData data {1};
             _sharedData->addTcpPacketToSendToSpecificPlayer(playerId, data);
             return;
         }

         int const currentPlayers = _sharedData->getNumberPlayerLobby(lobby->id);
         if (currentPlayers >= cmn::maxPlayers) {
             cmn::errorTcpData data {2};
             _sharedData->addTcpPacketToSendToSpecificPlayer(playerId, data);
             return;
         }

         _sharedData->addPlayerToLobby(playerId, lobby->id);
         cmn::joinLobbyData joinData = {
             static_cast<uint32_t>(lobby->id),
             static_cast<uint8_t>(lobby->type),
             static_cast<uint32_t>(lobby->code)
         };
         _sharedData->addLobbyTcpPacketToSend(lobby->id, joinData);
         if (currentPlayers + 1 >= cmn::maxPlayers) {
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
        size_t const currentPlayerCount = _sharedData->getPlayerListSize();

        if (currentPlayerCount < _lastPlayerCount) {
            std::vector<int> allPlayerIds = _sharedData->getAllPlayerIds();

            std::queue<int> newMatchmakingQueue;
            while (!_matchmakingQueue.empty()) {
                int const playerId = _matchmakingQueue.front();
                _matchmakingQueue.pop();
                if (std::ranges::find(allPlayerIds, playerId) != allPlayerIds.end()) {
                    newMatchmakingQueue.push(playerId);
                } else {
                    _playersInMatchmaking.erase(playerId);
                }
            }
            _matchmakingQueue = std::move(newMatchmakingQueue);

            for (auto it = _lobbyMap.begin(); it != _lobbyMap.end(); ) {
                int const lobbyId = it->first;
                auto const lobbyPlayers = _sharedData->getLobbyPlayers(lobbyId);

                for (int const playerId : lobbyPlayers) {
                    if (std::ranges::find(allPlayerIds, playerId) == allPlayerIds.end()) {
                        _sharedData->removePlayerFromLobby(playerId, lobbyId);
                    }
                }
                if (_sharedData->getNumberPlayerLobby(lobbyId) == 0) {
                    _sharedData->setLobbyState(lobbyId, cmn::LobbyState::EndGame);
                    if (_activeGames.contains(lobbyId)) {
                        _activeGames.erase(lobbyId);
                    }
                    it = _lobbyMap.erase(it);
                    std::cout << "Lobby " << lobbyId << " removed" << std::endl;
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

         auto lobbyState = _lobbyMap[lobbyId].type == cmn::Lobby ? cmn::LobbyState::Waiting : cmn::LobbyState::Running;
         _lobbyMap[lobbyId].state = lobbyState;
         _sharedData->setLobbyState(lobbyId, _lobbyMap[lobbyId].state);

        _activeGames[lobbyId] = std::jthread([this, lobbyId]() {
            try {
                Game game(_sharedData, lobbyId, _lobbyMap[lobbyId].type);
                std::cout << "===============================================" << std::endl;
                std::cout << "Game launched in lobby: " << lobbyId << std::endl;
                for (auto id: _sharedData->getLobbyPlayers(lobbyId))
                    std::cout << id << std::endl;
                std::cout << "===============================================" << std::endl;
                game.run();
            } catch (const std::exception &e) {
                std::cerr << "Game error in lobby " << lobbyId << ": " << e.what() << "\n";
            }
        });
    }

    void LobbyManager::_cleanupFinishedGames()
    {
         // TODO: implement that in game,
        for (auto it = _lobbyMap.begin(); it != _lobbyMap.end(); ) {
            int const lobbyId = it->first;
            if (_sharedData->getLobbyState(lobbyId) == cmn::LobbyState::EndGame) {
                if (_activeGames.contains(lobbyId)) {
                    _activeGames.erase(lobbyId);
                }
                _sharedData->deleteLobby(lobbyId);
                it = _lobbyMap.erase(it);
                std::cout << "deleting lobby: " << lobbyId << std::endl;
            } else {
                ++it;
            }
        }
    }

    int LobbyManager::_createLobbyCode()
    {
        return rand() % 900000 + 100000;
    }

    Lobby* LobbyManager::_findLobbyByCode(const int code)
    {
        for (auto &lobby : _lobbyMap | std::views::values) {
            if (lobby.type == cmn::LobbyType::Lobby && lobby.code == code) {
                return &lobby;
            }
        }
        return nullptr;
    }

}