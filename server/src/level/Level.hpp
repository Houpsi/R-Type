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
            std::string enemySpritePath,
            uint8_t enemySpawnRate,
            bool isBossPresent,
            std::string bossSpritePath,
            uint32_t bossApparitionTime
        );
        [[nodiscard]] uint8_t getEnemySpawnRate() const;
        [[nodiscard]] bool getIsBossPresent() const;
        [[nodiscard]] uint32_t getBossApparitionTime() const;
        [[nodiscard]] std::string getEnemySpritePath() const;
        [[nodiscard]] std::string getBossSpritePath() const;
        [[nodiscard]] uint8_t getLevelId() const;

      private:
        uint8_t _levelId;
        uint8_t _enemySpawnRate;
        bool _isBossPresent;
        uint32_t _bossApparitionTime;
        std::string _enemySpritePath;
        std::string _bossSpritePath;
    };

}// namespace server

#endif// R_TYPE_LEVEL_HPP
