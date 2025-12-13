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
        std::string enemySpritePath,
        uint8_t enemySpawnRate,
        bool isBossPresent,
        std::string bossSpritePath,
        uint32_t bossApparitionTime
    ) : _levelId(levelId),
        _enemySpawnRate(enemySpawnRate),
        _isBossPresent(isBossPresent),
        _bossApparitionTime(bossApparitionTime),
        _enemySpritePath(std::move(enemySpritePath)),
        _bossSpritePath(std::move(bossSpritePath)) {}

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

    std::string Level::getEnemySpritePath() const
    {
        return _enemySpritePath;
    }

    std::string Level::getBossSpritePath() const
    {
        return _bossSpritePath;
    }

    uint8_t Level::getLevelId() const
    {
        return _levelId;
    }

}// namespace server