/*
** EPITECH PROJECT, 2025
** R_Type
** File description:
** LevelManager
*/

#include "LevelManager.hpp"
#include "parser/LevelParser.hpp"
#include <filesystem>

namespace server {

    void LevelManager::addLevel(Level &level)
    {
        _levels.push_back(level);
    }

    void LevelManager::loadLevelFromFolder()
    {
        LevelParser parser;
        const std::string nameFolder = static_cast<std::string>(cmn::folderLevels);

        for (const auto& entry : std::filesystem::directory_iterator(cmn::folderLevels)) {
            if (std::filesystem::is_regular_file(entry.path())) {
                Level level;
                if (!parser.createLevel(nameFolder + '/' + entry.path().filename().string(), level)) {
                    continue;
                }
                _levels.push_back(level);
            }
        }
    }

    Level &LevelManager::getCurrentLevel()
    {
        for (auto &level : _levels) {
            if (level.getLevelId() == _currentLevelId) {
                return level;
            }
        }
        throw std::exception();
    }

    void LevelManager::setCurrentLevelId(uint8_t id)
    {
        _currentLevelId = id;
    }

    void LevelManager::changeToNextLevel()
    {
        bool found = false;
        uint8_t nextId = 0;
        uint8_t tmpCurrent = _currentLevelId;

        for (const auto &level : _levels) {
            uint8_t id = level.getLevelId();
            if (id > _currentLevelId) {
                if (!found || id < nextId) {
                    nextId = id;
                    found = true;
                }
            }
        }
        if (!found) {
            _currentLevelId = tmpCurrent;
            return;
        }
        _currentLevelId = nextId;
    }
}// namespace server