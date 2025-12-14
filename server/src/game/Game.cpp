/*
** EPITECH PROJECT, 2025
** R_Type
** File description:
** Game
*/

#include "Game.hpp"
#include "components/Collision.hpp"
#include "components/Health.hpp"
#include "components/InputPlayer.hpp"
#include "components/Position.hpp"
#include "components/Shoot.hpp"
#include "systems/CollisionSystem.hpp"
#include "systems/DestroySystem.hpp"
#include "systems/HealthSystem.hpp"
#include "systems/MovementSystem.hpp"
#include "systems/ShootSystem.hpp"
#include "systems/VelocitySystem.hpp"

namespace server {

     Game::Game(const std::shared_ptr<cmn::SharedData> &data): _sharedData(data) {}

    void Game::run()
    {
//        _initLevels();
//        _initEcsManager();
//
//        Level &currentLevel = _levelManager.getCurrentLevel();
//        sf::Clock clock;
//        sf::Clock enemyClock;
//
//         while (true) {
//             float const deltaTime = clock.restart().asSeconds();
//
//             _ecs.setDeltaTime(deltaTime);
//             _ecs.updateSystems();
//
//             for (auto &entity : )
//
//             std::optional<cmn::packetData> data = _sharedData->getReceivedPacket();
//             if (data.has_value()) {
//
//             }
//         }
    }

    void Game::_initLevels()
    {
        uint8_t levelId = 1;
        uint8_t enemySpawnRate = 10;
        bool isBossPresent = false;
        uint32_t bossApparitionTiming = 0;

        server::Level firstLevel(levelId, enemySpawnRate, isBossPresent, bossApparitionTiming);

        _levelManager.addLevel(firstLevel);
        _levelManager.setCurrentLevelId(1);
    }

    void Game::_initEcsManager()
    {
        constexpr uint16_t playerHeight = 17;
        constexpr uint16_t playerWidth = 33;
        constexpr uint8_t playerHealth = 100;
        constexpr uint16_t playerPosX = 200;
        constexpr uint16_t playerPosY = 540;
        constexpr uint8_t damage = 50;
        constexpr float cooldown = 0.5;

        auto player = _ecs.createEntity();

        player->addComponent<ecs::Health>(playerHealth);
        player->addComponent<ecs::Position>(playerPosX, playerPosY);
        player->addComponent<ecs::InputPlayer>();

        player->addComponent<ecs::Collision>(ecs::TypeCollision::PLAYER, playerWidth, playerHeight);
        player->addComponent<ecs::Shoot>(damage, cooldown);

        _ecs.addSystem<ecs::MovementSystem>();
        _ecs.addSystem<ecs::CollisionSystem>();
        _ecs.addSystem<ecs::ShootSystem>();
        _ecs.addSystem<ecs::VelocitySystem>();
        _ecs.addSystem<ecs::HealthSystem>();
        _ecs.addSystem<ecs::DestroySystem>();
    }

}