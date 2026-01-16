/*
** EPITECH PROJECT, 2026
** R_Type
** File description:
** LobbyManager
*/

#ifndef R_TYPE_LOBBYMANAGER_HPP
#define R_TYPE_LOBBYMANAGER_HPP
#include "data_translator/DataTranslator.hpp"
#include "enums/LobbyState.hpp"
#include "enums/LobbyType.hpp"
#include "server_shared_data/ServerSharedData.hpp"
#include <queue>
#include <thread>
#include <unordered_set>


namespace server {

    using Lobby = struct Lobby {
        int id;
        cmn::LobbyType type;
        cmn::LobbyState state;
        int code;
        std::chrono::steady_clock::time_point createdAt;

        Lobby() : id(-1), type(cmn::LobbyType::Solo),
                  state(cmn::LobbyState::Waiting), code(0),
                  createdAt(std::chrono::steady_clock::now()) {}
    };

    class LobbyManager
    {
        public:
            explicit LobbyManager(const std::shared_ptr<ServerSharedData>&);
            ~LobbyManager();

            [[noreturn]] void run();
        private:
        std::queue<int> _matchmakingQueue;
        std::shared_ptr<ServerSharedData> _sharedData;
        std::unordered_map<int, Lobby> _lobbyMap;
        std::unordered_map<int, std::jthread> _activeGames;
        std::unordered_set<int> _playersInMatchmaking;
        size_t _lastPlayerCount;

        void _launchGame(int lobbyId);
        static Lobby _createLobby(cmn::LobbyType lobbyType);
        void _joinLobby(int code, int playerId);
        void _leaveLobby(int playerId);
        void _handleMatchMaking();
        void _handlePlayerDisconnections();
        void _cleanupFinishedGames();
        static int _createLobbyCode();
        void _getPacketType(cmn::packetData &data);
        Lobby* _findLobbyByCode(int code);
        void _checkModeSelected(cmn::selectModeData data);
    };
}


#endif// R_TYPE_LOBBYMANAGER_HPP
