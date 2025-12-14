/*
** EPITECH PROJECT, 2025
** R_Type
** File description:
** Game
*/

#ifndef R_TYPE_GAME_HPP
#define R_TYPE_GAME_HPP

#include "EcsManager.hpp"
#include "level_manager/LevelManager.hpp"
#include "shared_data/SharedData.hpp"

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
        void _createNewPlayers(const std::vector<int>& ids, size_t &currentNbPlayerEntities);
        bool _isIdAlreadyPresent(int playerId);
    };
}

#endif //R_TYPE_GAME_HPP
