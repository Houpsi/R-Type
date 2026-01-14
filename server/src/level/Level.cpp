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

    uint8_t Level::getNumberWaves() const
    {
        return _numberWaves;
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

    void Level::setNumberWaves(uint8_t numberWaves)
    {
        _numberWaves = numberWaves;
    }

    void Level::setPlayerSpeed(uint16_t playerSpeed)
    {
        _playerSpeed = playerSpeed;
    }

    void Level::addWave(uint16_t time, std::list<tmpEnemy> enemies)
    {
        _waves.emplace_back(time, enemies);
    }

    std::list<std::pair<uint16_t, std::list<tmpEnemy>>> Level::getWaves() const
    {
        return _waves;
    }


}// namespace server