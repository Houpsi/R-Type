/*
** EPITECH PROJECT, 2025
** R_Type
** File description:
** Level
*/

#ifndef R_TYPE_LEVEL_HPP
#define R_TYPE_LEVEL_HPP

#include <cstdint>
#include <string>
namespace server {

    class Level
    {
      public:
        Level(
            uint8_t levelId,
            uint8_t enemySpawnRate,
            bool isBossPresent,
            uint32_t bossApparitionTime
        );
        [[nodiscard]] uint8_t getEnemySpawnRate() const;
        [[nodiscard]] bool getIsBossPresent() const;
        [[nodiscard]] uint32_t getBossApparitionTime() const;
        [[nodiscard]] uint8_t getLevelId() const;

      private:
        uint8_t _levelId;
        uint8_t _enemySpawnRate;
        bool _isBossPresent;
        uint32_t _bossApparitionTime;
    };

}// namespace server

#endif// R_TYPE_LEVEL_HPP
