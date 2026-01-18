/*
** EPITECH PROJECT, 2025
** R_Type
** File description:
** Constants
*/

#ifndef R_TYPE_GAMECONSTANTS_HPP
#define R_TYPE_GAMECONSTANTS_HPP

#include "SFML/System/Vector2.hpp"
#include "enums/EntityType.hpp"

#include <array>
#include <cstdint>
#include <map>
#include <string>
#include <unordered_map>

namespace cmn {

    constexpr int maxPlayers = 2;

    constexpr uint8_t numberPlayerOnSprite = 5;
    constexpr float playerHealth = 100;
    constexpr uint16_t playerSpeed = 250;
    constexpr sf::Vector2f playerSpriteScale = {2.0F, 2.0F};
    constexpr std::string_view playerSpriteSheet = "./assets/r-typesheet42.gif";
    constexpr uint8_t playerHeight= 34;
    constexpr uint8_t playerWidth = 66;
    constexpr uint8_t playerDamage = 50;
    constexpr float playerCoolDown = 0.5;
    constexpr std::string_view playerShootSound = "./assets/sound/shoot.wav";
    constexpr uint16_t playerPosX = 200;
    constexpr uint16_t playerPosY = 540;

    constexpr uint8_t monsterHealth = 100;
    constexpr uint8_t monsterDamage = 100;
    constexpr uint16_t monsterSpeed = 250;
    constexpr uint8_t monsterShootCooldown = 3;
    constexpr sf::Vector2f monsterSpriteScale = {2.0F, 2.0F};
    constexpr std::string_view monsterSpriteSheet = "./assets/r-typesheet5.gif";
    constexpr std::pair<uint8_t, uint8_t> monsterAnimationSize = {33, 24};
    constexpr uint8_t monsterAnimationOffset = 0;
    constexpr uint8_t monsterAnimationNumberFrame = 8;
    constexpr uint8_t monsterCollisionWidth = 33;
    constexpr uint8_t monsterCollisionHeight = 24;
    constexpr uint16_t monsterSpawnPositionWidth = 2020;
    constexpr uint16_t monsterMaxSpawnPositionHeight = 1081;

    constexpr uint8_t monster2Health = 100;
    constexpr sf::Vector2f monster2SpriteScale = {1.0F, 1.0F};
    constexpr uint16_t monster2Speed = 400;
    constexpr uint8_t monster2ShootCooldown = 2;
    constexpr std::string_view monster2SpriteSheet = "./assets/r-typesheet211.gif";
    constexpr std::pair<uint8_t, uint8_t> monster2AnimationSize = {64, 50};
    constexpr uint8_t monster2AnimationOffset = 0;
    constexpr uint8_t monster2AnimationNumberFrame = 4;
    constexpr uint8_t monster2CollisionWidth = 64;
    constexpr uint8_t monster2CollisionHeight = 50;
    constexpr uint16_t monster2SpawnPositionWidth = 2020;
    constexpr uint16_t monster2MaxSpawnPositionHeight = 1081;

    constexpr uint16_t monsterProjectileSpeed = 400;
    constexpr int8_t monsterProjectileDirection = 0;
    constexpr std::string_view monsterProjectileSpriteSheet = "./assets/r-typesheet43c.gif";
    constexpr sf::Vector2f monsterProjectileScale = {3.0F, 3.0F};
    constexpr std::pair<uint8_t, uint8_t> monsterProjectileAnimationSize = { 17, 6 };
    constexpr uint8_t monsterProjectileAnimationOffset = 0;
    constexpr uint8_t monsterProjectileAnimationNumberFrame = 8;
    constexpr uint8_t monsterProjectileCollisionWidth = 17;
    constexpr uint8_t monsterProjectileCollisionHeight = 6;
    constexpr uint8_t monsterProjectileSoundId = 1;
    constexpr bool monsterProjectileLoop = false;

    constexpr uint8_t boss1Health = 100;
    constexpr sf::Vector2f boss1SpriteScale = {2.0F, 2.0F};
    constexpr std::string_view boss1SpriteSheet = "./assets/r-typesheet30e.gif";
    constexpr std::pair<uint8_t, uint8_t> boss1AnimationSize = {161, 207};
    constexpr uint8_t boss1AnimationOffset = 0;
    constexpr uint8_t boss1AnimationNumberFrame = 4;
    constexpr uint8_t boss1CollisionWidth = 160;
    constexpr uint8_t boss1CollisionHeight = 207;
    constexpr uint16_t boss1SpawnPositionWidth = 1500;
    constexpr uint16_t boss1SpawnPositionHeight = 250;
    constexpr uint8_t bossSoundId = 4;


    constexpr sf::Vector2f pwShootSpriteScale = {2.0F, 2.0F};
    constexpr std::string_view pwShootSpriteSheet = "./assets/r-typesheet2d.gif";
    constexpr std::pair<uint8_t, uint8_t> pwShootAnimationSize = {24, 18};
    constexpr uint8_t pwShootAnimationOffset = 0;
    constexpr uint8_t pwShootAnimationNumberFrame = 6;
    constexpr uint8_t pwShootCollisionWidth = 23;
    constexpr uint8_t pwShootCollisionHeight = 18;
    constexpr uint16_t pwShootSpeed = 200;
    constexpr int8_t pwShootProjectileDirection = 0;

    constexpr uint16_t playerProjectileSpeed = 400;
    constexpr int8_t playerProjectileDirection = 1;
    constexpr sf::Vector2f playerProjectileScale = {1.0F, 1.0F};
    constexpr std::string_view playerProjectileSpriteSheet = "./assets/r-typesheet30a.gif";
    constexpr std::pair<uint8_t, uint8_t> playerProjectileAnimationSize = {32, 36};
    constexpr uint8_t playerProjectileAnimationOffset = 0;
    constexpr uint8_t playerProjectileAnimationNumberFrame = 3;
    constexpr uint8_t playerProjectileCollisionWidth = 32;
    constexpr uint8_t playerProjectileCollisionHeight = 36;
    constexpr uint8_t playerProjectileSoundId = 1;
    constexpr bool playerProjectileLoop = false;

    constexpr sf::Vector2f backgroundSpriteScale = {1.0F, 1.0F};
    constexpr std::string_view pathBackgroundStars = "./assets/bg-stars.png";
    constexpr std::string_view pathBackgroundPlanets = "./assets/planets_background.png";
    constexpr sf::Vector2f posZero(0.0F, 0.0F);
    constexpr sf::Vector2f posOne(1920.0F, 0.0F);
    constexpr sf::Vector2f posTwo(3840.0F, 0.0F);
    constexpr int idBg1 = 0;
    constexpr int idBg2 = 1;
    constexpr int idStart1 = 2;
    constexpr int idStart2 = 3;
    constexpr sf::Vector2f veloStars(10.0F, 0.5F);
    constexpr sf::Vector2f veloPlanets(20.0F, 0.5F);
    constexpr int sizeStars = 1920;
    constexpr int sizePlanets = 3840;

    constexpr uint16_t windowWidth = 1920;
    constexpr uint16_t windowHeight = 1080;

    static constexpr int MAX_ENTITIES = 6;
    static constexpr int MAX_DEPTH = 6;

    constexpr std::string_view folderLevels = "Levels";
    constexpr std::array<std::string_view, 2> nameTypeEnemies = {"plane_enemy", "crochet_enemy"};
    constexpr std::array<std::string_view, 2> nameTypeBoss = {"boss_type_1", "boss_type_2"};
    constexpr std::string_view configClientFile = "config/client.cfg";

    constexpr int idEntityForMusic = 5;
    constexpr int idThemeMusic = 2;

    constexpr int idEntityForScore = 8;
    constexpr int idExplosionMusic = 3;

    constexpr float positionScoreX = 20.F;
    constexpr float positionScoreY = 20.F;
    constexpr int sizeScore = 32;
    constexpr std::string_view fontPath = "./assets/font/font.ttf";
}

#endif// R_TYPE_GAMECONSTANTS_HPP
