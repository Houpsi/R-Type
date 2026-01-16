/*
** EPITECH PROJECT, 2025
** R_Type
** File description:
** Level
*/

#include "Level.hpp"
#include <iostream>
#include <utility>

namespace server {

    uint8_t Level::getEnemySpawnRate() const
    {
        return _enemySpawnRate;
    }

    bool Level::getIsBossPresent() const
    {
        return _isBossPresent;
    }

    void Level::setIsBossPresent(bool isPresent)
    {
        _isBossPresent = isPresent;
    }

    uint8_t Level::getLevelId() const
    {
        return _levelId;
    }

    void Level::setLevelId(uint8_t levelId)
    {
        _levelId = levelId;
    }

     std::pair <std::string, uint32_t> Level::getBoss() const
    {
        return _boss;
    }

    std::string Level::getNameLevel() const
    {
        return _nameLevel;
    }

    uint8_t Level::getRepeatWaves() const
    {
        return _repeatWaves;
    }

    uint16_t Level::getPlayerSpeed() const
    {
        return _playerSpeed;
    }

    void Level::setBoss(std::string boss, uint32_t healthBoss)
    {
        _boss = std::make_pair(boss, healthBoss);
    }

    void Level::setNameLevel(const std::string &nameLevel)
    {
        _nameLevel = nameLevel;
    }

    void Level::setRepeatWaves(uint8_t repeatWaves)
    {
        _repeatWaves = repeatWaves;
    }

    void Level::setPlayerSpeed(uint16_t playerSpeed)
    {
        _playerSpeed = playerSpeed;
    }

    void Level::addWave(uint16_t time, std::list<tmpEnemy> enemies)
    {
        _waves.emplace_back(time, enemies);
    }

    const std::vector<std::pair<uint16_t, std::list<tmpEnemy>>>& Level::getWaves() const
    {
        return _waves;
    }

    std::vector<std::pair<uint16_t, std::list<tmpEnemy>>> &Level::getWaves()
    {
        return _waves;
    }


    int Level::getCurrentWaveId() const
    {
        return  _currentWave;
    }

    void Level::setCurrentWave(int id)
    {
        _currentWave = id;
    }

    void Level::nextWave()
    {
        _currentWave++;

        if (_currentWave >= _waves.size()) {
            _currentWave = 0;
            _currentRepeat++;
        }
    }

    bool Level::isFinished() const
    {
        return _currentRepeat >= static_cast<int>(_totalRepeatWaves);
    }

    void Level::calculateNumberTotalWave()
    {
        _totalRepeatWaves = static_cast<int>(_waves.size()) * _repeatWaves;
    }

    bool Level::hasBossSpawned() const
    {
        return _bossHasSpawned;
    }
    void Level::setBossSpawned(bool spawned)
    {
        _bossHasSpawned = spawned;
    }

}// namespace server