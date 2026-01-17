/*
** EPITECH PROJECT, 2026
** R_Type
** File description:
** LevelParser
*/


#ifndef R_TYPE_LEVELPARSER_HPP
#define R_TYPE_LEVELPARSER_HPP
#include "level/Level.hpp"
#include <libconfig.h++>
#include <stdexcept>
#include <unordered_set>

namespace server {
    class LevelParser
    {
        public:
            LevelParser() = default;
            bool createLevel(const std::string &fileConfigLevel, Level &baseLevel);

            class LevelParserException : public std::exception
            {
                private:
                    std::string message;
                public:
                explicit LevelParserException(const char* msg) : message(msg) {}

                [[nodiscard]] const char* what() const noexcept override {
                    return message.c_str();
                }
            };
        private:
            void _parsePrerequisites(const libconfig::Setting& root, Level &newLevel);
            static void _parseWaves(const libconfig::Setting& root, Level &newLevel);
            static void _parseBoss(const libconfig::Setting& root, Level &newLevel);
            void _checkIdExists(const int id);
            static void _isValidEnemyType(const std::string& type);
            static void _isValidBossType(const std::string& type);
            static cmn::EntityType _entityTypeFromString(const std::string& type);
            std::unordered_set<int> _idAlreadyExists;
    };
}



#endif// R_TYPE_LEVELPARSER_HPP
