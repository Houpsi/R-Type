/*
** EPITECH PROJECT, 2026
** R_Type
** File description:
** LevelParser
*/


#include "LevelParser.hpp"
#include <cstdint>
#include <iostream>

namespace server {

    bool LevelParser::createLevel(const std::string &fileConfigLevel, Level &baseLevel)
    {
        Level newLevel;
        libconfig::Config config;

        try {
            config.readFile(fileConfigLevel.c_str());
            const libconfig::Setting& root = config.lookup("level");
            _parsePrerequisites(root, newLevel);
            _parseWaves(root, newLevel);
            _parseBoss(root, newLevel);
            baseLevel = newLevel;
            return true;
        } catch(const libconfig::ParseException &pex) {
            std::cerr << "Parse error at " << pex.getFile() << ":" << pex.getLine() << " - " << pex.getError() << '\n';
            return false;
        } catch(const libconfig::FileIOException &fioex) {
            std::cerr << "I/O error while reading file." << '\n';
            return false;
        } catch(const LevelParserException &e) {
            std::cerr << e.what() << '\n';
            return false;
        }
    }

    void LevelParser::_checkIdExists(const int id)
    {
        if (_idAlreadyExists.contains(id)) {
            throw LevelParserException("Id already exists");
        }
        _idAlreadyExists.insert(id);
    }

    void LevelParser::_parsePrerequisites(const libconfig::Setting &root, Level &newLevel)
    {
        constexpr int maxId = 255;

        const int id = root.lookup("id");
        const std::string name = root.lookup("name");
        const int scrollSpeed = root.lookup("scroll_speed");

        if (id < 0 || id > maxId) {
            throw LevelParserException("Level ID out of range");
        }
        _checkIdExists(id);
        newLevel.setLevelId(static_cast<uint8_t>(id));
        newLevel.setNameLevel(name);
        if (scrollSpeed <= 0) {
            throw LevelParserException("Scroll Speed out of range");
        }
        newLevel.setPlayerSpeed(static_cast<uint16_t>(scrollSpeed));
    }

    void LevelParser::_parseWaves(const libconfig::Setting &root, Level &newLevel)
    {
        const libconfig::Setting& wavesSetting = root["waves"];
        const int repeatWaves = root.lookup("waves_repeat");
        const int numDifferentWaves = wavesSetting.getLength();
        newLevel.setCurrentWave(0);

        if (repeatWaves <= 0) {
            throw LevelParserException("Wave repeat is out of range");
        }
        newLevel.setRepeatWaves(static_cast<uint8_t>(repeatWaves));

        for (int i = 0; i < numDifferentWaves; ++i) {
            const libconfig::Setting &waveSetting = wavesSetting[i];
            const int timeOfWave =  waveSetting.lookup("time");

            std::list<tmpEnemy> enemies;
            const libconfig::Setting& enemiesSetting = waveSetting["enemies"];
            const int numEnemies = enemiesSetting.getLength();

            for (int j = 0; j < numEnemies; ++j) {
                tmpEnemy newEnemy;
                const libconfig::Setting& enemySetting = enemiesSetting[j];
                const std::string type = enemySetting.lookup("type");
                const float countEnemy = enemySetting.lookup("count");
                if (countEnemy <= 0.0) {
                    throw LevelParserException("Number of Enemy out of range");
                }
                newEnemy.spawnRate = countEnemy;
                _isValidEnemyType(type);
                newEnemy.type = _entityTypeFromString(type);
                enemies.push_back(newEnemy);
            }
            if (timeOfWave <= 0) {
                throw LevelParserException("Time of wave out of range");
            }
            newLevel.addWave(timeOfWave, enemies);
        }
        newLevel.calculateNumberTotalWave();
    }

    cmn::EntityType LevelParser::_entityTypeFromString(const std::string &type)
    {
        std::map<std::string, cmn::EntityType> keyEnemyToEnum = {
            { "plane_enemy" , cmn::EntityType::Plane },
            { "crochet_enemy", cmn::EntityType::Crochet}
        };

        auto it = keyEnemyToEnum.find(type);
        if (it != keyEnemyToEnum.end()) {
            return it->second;
        }
        throw LevelParserException("Unknown type Enemy");
    }

    void LevelParser::_isValidEnemyType(const std::string& type)
    {
        for (auto validType : cmn::nameTypeEnemies) {
            if (type == validType) {
                return;
            }
        }
        throw LevelParserException("Unknown type Enemy");
    }

    void LevelParser::_isValidBossType(const std::string& type)
    {
        for (auto validType : cmn::nameTypeBoss) {
            if (type == validType) {
                return;
            }
        }
        throw LevelParserException("Unknown type Boss");
    }

    void LevelParser::_parseBoss(const libconfig::Setting& root, Level &newLevel)
    {
        if (!root.exists("boss")) {
            newLevel.setIsBossPresent(false);
            return;
        }

        int const hp = root.lookup("boss.hp");
        std::string const type = root.lookup("boss.type");
        _isValidBossType(type);
        newLevel.setIsBossPresent(true);

        if (hp <= 0) {
            throw LevelParserException("Health of boss out of range");
        }
        newLevel.setBoss(type, static_cast<uint32_t>(hp));
    }
}// namespace server
