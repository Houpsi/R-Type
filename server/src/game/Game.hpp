/*
** EPITECH PROJECT, 2025
** R_Type
** File description:
** Game
*/

#ifndef R_TYPE_GAME_HPP
#define R_TYPE_GAME_HPP

#include "EcsManager.hpp"
#include "SFML/System/Clock.hpp"
#include "enums/LobbyType.hpp"
#include "level_manager/LevelManager.hpp"
#include "server_shared_data/ServerSharedData.hpp"
#include "shared_data/SharedData.hpp"
#include <random>

namespace server {
    class Game {
    public:
        explicit Game(
            const std::shared_ptr<ServerSharedData>&,
            int lobbyId,
            cmn::LobbyType lobbyType);
        ~Game() = default;
        [[noreturn]] void run();
    private:
        ecs::EcsManager _ecs;
        std::shared_ptr<ServerSharedData> _sharedData;
        LevelManager _levelManager;
        std::vector<int> _readyPlayersId;
        std::unordered_map<int, uint64_t> _playerIdEntityMap;
        std::unordered_map<uint64_t , int> _entityIdPlayerMap;
        int _lobbyId;
        cmn::LobbyType _lobbyType;

        void _initLevels();
        void _initEcsManager();
        void _createNewPlayers(const std::vector<int>& ids, size_t &currentNbPlayerEntities);
        bool _isIdAlreadyPresent(int playerId);
        void _waitForPlayers();
        void _sendPlayerEntities();
        [[noreturn]] void _startGame();
        void _createEnemy(const Level &currentLevel, sf::Clock &enemyClock, std::minstd_rand0 &generator);
        void _checkSpaceBar();
        void _sendPositions();
        void _sendDestroy();
    };
}

#endif //R_TYPE_GAME_HPP
