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
#include "enums/GameResultType.hpp"
#include "enums/LobbyType.hpp"
#include "level_manager/LevelManager.hpp"
#include "server_shared_data/ServerSharedData.hpp"
#include <random>

namespace server {
    class Game {
    public:
        explicit Game(
            const std::shared_ptr<ServerSharedData>&,
            int lobbyId,
            cmn::LobbyType lobbyType);
        ~Game() = default;
        void run();
    private:
        ecs::EcsManager _ecs;
        std::shared_ptr<ServerSharedData> _sharedData;
        LevelManager _levelManager;
        std::vector<int> _readyPlayersId;
        std::unordered_map<int, uint64_t> _playerIdEntityMap;
        std::unordered_map<uint64_t , int> _entityIdPlayerMap;
        int _currentIdBoss = -1;
        int _lobbyId;
        cmn::LobbyType _lobbyType;
        std::vector<int> _deadPlayersId;

        void _checkBossDeath(Level &currentLevel, sf::Clock &enemyClock);
        void _initLevels();
        void _initEcsManager();
        void _createNewPlayers(const std::vector<int>& ids, size_t &currentNbPlayerEntities);
        bool _isIdAlreadyPresent(int playerId);
        void _waitForPlayers();
        void _sendSound() const;
        void _sendPlayerEntities();
        void _startGame();
        void _createEnemy(Level &currentLevel, sf::Clock &enemyClock, std::minstd_rand0 &generator);
        void _checkSpaceBar();
        void _sendPositions();
        void _sendDestroy();
        void _checkPlayerDeaths(const std::shared_ptr<ecs::Entity> &entity);
        bool _areAllPlayersDead() const;
        void _handleDisconnectedPlayers();
        void _sendGameEndState(cmn::GameResultType type) const;
        void _enemyShoot();
        void _sendText();
        void _createBonus(Level &currentLevel, sf::Clock &bonusClock, std::minstd_rand0 &generator);
        float _nextBonusSpawnDelay = 5.0f;
        std::unordered_map<uint32_t, std::pair<float, float>> _entityPos;
        uint32_t _score = 0;
    };
}

#endif //R_TYPE_GAME_HPP
