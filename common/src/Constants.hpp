/*
** EPITECH PROJECT, 2025
** R_Type
** File description:
** Constants
*/

#ifndef R_TYPE_CONSTANTS_HPP
#define R_TYPE_CONSTANTS_HPP

#include "SFML/System/Vector2.hpp"
#include <string>
#include <cstdint>

namespace cmn {

    constexpr float playerHealth = 100;
    constexpr sf::Vector2f playerSpriteScale = {2.0f, 2.0f};
    constexpr std::string_view playerSpriteSheet = "./assets/r-typesheet42.gif";
    constexpr uint8_t playerHeight= 17;
    constexpr uint8_t playerWidth = 33;
    constexpr uint8_t playerDamage = 50;
    constexpr float playerCoolDown = 0.5;
    constexpr std::string_view playerShootSound = "./assets/sound/shoot.wav";

    constexpr uint8_t monsterHealth = 100;
    constexpr sf::Vector2f monsterSpriteScale = {2.0f, 2.0f};
    constexpr std::string_view monsterSpriteSheet = "./assets/r-typesheet5.gif";
    constexpr std::pair<uint8_t, uint8_t> monsterAnimationSize = {32, 36};
    constexpr uint8_t monsterAnimationOffset = 0;
    constexpr uint8_t monsterAnimationNumberFrame = 8;
    constexpr uint8_t monsterCollisionHeight = 14;
    constexpr uint8_t monsterCollisionWidth = 18;

    constexpr uint16_t playerProjectileSpeed = 400;
    constexpr int8_t playerProjectileDirection = 1;
    constexpr sf::Vector2f playerProjectileScale = {1.0f, 1.0f};
    constexpr std::string_view playerProjectileSpriteSheet = "./assets/r-typesheet30a.gif";
    constexpr std::pair<uint8_t, uint8_t> playerProjectileAnimationSize = {32, 36};
    constexpr uint8_t playerProjectileAnimationOffset = 0;
    constexpr uint8_t playerProjectileAnimationNumberFrame = 8;
    constexpr uint8_t playerProjectileCollisionHeight = 10;
    constexpr uint8_t playerProjectileCollisionWidth = 10;


}

#endif// R_TYPE_CONSTANTS_HPP
