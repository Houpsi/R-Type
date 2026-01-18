/*
** EPITECH PROJECT, 2025
** R_Type
** File description:
** Level
*/

#ifndef R_TYPE_LEVEL_HPP
#define R_TYPE_LEVEL_HPP

#include "constants/GameConstants.hpp"
#include <cstdint>
#include <list>
#include <string>
#include <vector>
#include "TmpEnemy.hpp"
namespace server {

    class Level
    {
      public:
        Level() = default;
        [[nodiscard]] uint8_t getEnemySpawnRate() const;
        [[nodiscard]] bool getIsBossPresent() const;
        void setIsBossPresent(bool isPresent);
        [[nodiscard]] uint8_t getLevelId() const;
        void setLevelId(uint8_t levelId);
        void setNameLevel(const std::string& _nameLevel);
        [[nodiscard]] std::string getNameLevel() const;
        void setPlayerSpeed(uint16_t playerSpeed);
        [[nodiscard]] uint16_t getPlayerSpeed() const;
        void setRepeatWaves(uint8_t numberWaves);
        [[nodiscard]] uint8_t getRepeatWaves() const;
        void setBoss(std::string boss, uint32_t healthBoss);
        [[nodiscard]] std::pair <std::string, uint32_t> getBoss() const;
        void addWave(uint16_t time, std::list<tmpEnemy> enemies);
        const std::vector <std::pair <uint16_t, std::list<tmpEnemy>>>& getWaves() const;
        std::vector <std::pair <uint16_t, std::list<tmpEnemy>>>& getWaves();
        void setCurrentWave(int id);
        int getCurrentWaveId() const;
        bool isFinished() const;
        void nextWave();
        void calculateNumberTotalWave();
        bool hasBossSpawned() const;
        void setBossSpawned(bool spawned);
        void setBonusSpawnRate(float spawnRate);
        float getBonusSpawnRate() const;
      private:
        uint8_t _levelId = 0;
        uint8_t _enemySpawnRate = 1;
        bool _isBossPresent = false;
        std::string _nameLevel;
        uint32_t _playerSpeed = cmn::playerSpeed;
        uint8_t _repeatWaves;
        std::pair <std::string, uint32_t> _boss;
        std::vector<std::pair <uint16_t, std::list<tmpEnemy>>> _waves;
        int _currentWave = 0;
        int _currentRepeat = 0;
        int _totalRepeatWaves = 0;
        bool _bossHasSpawned = false;
        float _bonusSpawnRate = 15.0f;
    };

}// namespace server

#endif// R_TYPE_LEVEL_HPP
