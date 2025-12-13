/*
** EPITECH PROJECT, 2025
** R_Type
** File description:
** LevelManager
*/

#ifndef R_TYPE_LEVELMANAGER_HPP
#define R_TYPE_LEVELMANAGER_HPP

#include "level/Level.hpp"
#include <list>
namespace server {

    class LevelManager
    {
      public:
        void addLevel(Level &level);
        Level &getCurrentLevel();
        void changeToNextLevel();
        void setCurrentLevelId(uint8_t id);

      private:
        std::list<Level> _levels;
        uint8_t _currentLevelId;
    };

}// namespace server

#endif// R_TYPE_LEVELMANAGER_HPP
