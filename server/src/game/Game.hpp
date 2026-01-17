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
#include "level_manager/LevelManager.hpp"
#include "shared_data/SharedData.hpp"
#include <random>

namespace server {
    class Game {
    public:
        explicit Game(const std::shared_ptr<cmn::SharedData>&);
        ~Game() = default;
        [[noreturn]] void run();
    private:
        ecs::EcsManager _ecs;
        std::shared_ptr<cmn::SharedData> _sharedData;
        LevelManager _levelManager;
        void _initLevels();
        void _initEcsManager();
        std::vector<int> _readyPlayersId;
        std::unordered_map<int, uint64_t> _playerIdEntityMap;
        std::unordered_map<uint64_t , int> _entityIdPlayerMap;
        int _currentIdBoss = -1;
        void _checkBossDeath(Level &currentLevel, sf::Clock &enemyClock);
        void _createNewPlayers(const std::vector<int>& ids, size_t &currentNbPlayerEntities);
        bool _isIdAlreadyPresent(int playerId);
        void _waitForPlayers();
        void _sendSound();
        void _sendPlayerEntities();
        [[noreturn]] void _startGame();
        void _createEnemy(Level &currentLevel, sf::Clock &enemyClock, std::minstd_rand0 &generator);
        void _checkSpaceBar();
        void _sendPositions();
        void _sendDestroy();
        void _enemyShoot();
        void _sendText();
        std::unordered_map<uint32_t, std::pair<float, float>> _entityPos;
    };
}

#endif //R_TYPE_GAME_HPP
