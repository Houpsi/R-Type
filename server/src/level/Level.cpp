/*
** EPITECH PROJECT, 2025
** R_Type
** File description:
** Level
*/

#include "Level.hpp"

#include <utility>

namespace server {

    Level::Level(
        uint8_t levelId,
        uint8_t enemySpawnRate,
        bool isBossPresent,
        uint32_t bossApparitionTime
    ) : _levelId(levelId),
        _enemySpawnRate(enemySpawnRate),
        _isBossPresent(isBossPresent),
        _bossApparitionTime(bossApparitionTime) {}

    uint8_t Level::getEnemySpawnRate() const
    {
        return _enemySpawnRate;
    }

    bool Level::getIsBossPresent() const
    {
        return _isBossPresent;
    }

    uint32_t Level::getBossApparitionTime() const
    {
        return _bossApparitionTime;
    }

    uint8_t Level::getLevelId() const
    {
        return _levelId;
    }

}// namespace server