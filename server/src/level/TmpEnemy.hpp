/*
** EPITECH PROJECT, 2026
** R_Type
** File description:
** Enemy
*/


#ifndef R_TYPE_TMPENEMY_HPP
#define R_TYPE_TMPENEMY_HPP
#include "enums/EntityType.hpp"

struct tmpEnemy
{
    cmn::EntityType type;
    float spawnRate;
    float lastSpawnTime = 0;
};


#endif// R_TYPE_TMPENEMY_HPP
