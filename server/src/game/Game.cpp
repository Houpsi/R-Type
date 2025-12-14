/*
** EPITECH PROJECT, 2025
** R_Type
** File description:
** Game
*/

#include "Game.hpp"
#include "Constants.hpp"
#include "components/Collision.hpp"
#include "components/Health.hpp"
#include "components/InputPlayer.hpp"
#include "components/Position.hpp"
#include "components/Shoot.hpp"
#include "data_translator/DataTranslator.hpp"
#include "packet_factory/PacketFactory.hpp"
#include "systems/CollisionSystem.hpp"
#include "systems/DestroySystem.hpp"
#include "systems/HealthSystem.hpp"
#include "systems/InputSystem.hpp"
#include "systems/MovementSystem.hpp"
#include "systems/ShootSystem.hpp"
#include "systems/VelocitySystem.hpp"
#include <algorithm>

namespace server {

     Game::Game(const std::shared_ptr<cmn::SharedData> &data): _sharedData(data)
     {
         try {
             ecs::EcsManager const manager {};
             _ecs = manager;
         } catch (std::exception &e) {
             throw std::exception();
         }
     }


    void Game::run()
    {
        _initLevels();

        size_t currentNbPlayerEntities = 0;
        size_t playerListSize = _sharedData->getPlayerListSize();

        while (_readyPlayersId.size() != playerListSize && playerListSize != 0) {
            playerListSize = _sharedData->getPlayerListSize();
            if (currentNbPlayerEntities != playerListSize) {
                _createNewPlayers(_sharedData->getAllPlayerIds(), currentNbPlayerEntities);
            }

            std::optional<cmn::packetData> data = _sharedData->getTcpReceivedPacket();

            if (!data.has_value()) {
                continue;
            }
            cmn::DataTranslator::translate(_ecs, data.value(), _playerIdEntityMap);

            auto entities = _ecs.getEntitiesWithComponent<ecs::InputPlayer>();

            for (auto &entity : entities) {
                if (entity->getComponent<ecs::InputPlayer>()->getRight()
                    && !_isIdAlreadyPresent(_entityIdPlayerMap[entity->getId()])) {
                    _readyPlayersId.push_back(_entityIdPlayerMap[entity->getId()]);
                }
            }
        }

//        _initEcsManager();
//
//        Level  const&currentLevel = _levelManager.getCurrentLevel();
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

    bool Game::_isIdAlreadyPresent(int playerId)
    {
        return std::ranges::any_of(
            _readyPlayersId,
            [playerId](int id) { return id == playerId; }
        );
    }

    void Game::_initLevels()
    {
        constexpr uint64_t level1SpawnRate = 10;

        uint8_t levelId = 1;
        uint8_t enemySpawnRate = level1SpawnRate;
        bool isBossPresent = false;
        uint32_t bossApparitionTiming = 0;

        server::Level firstLevel(levelId, enemySpawnRate, isBossPresent, bossApparitionTiming);

        _levelManager.addLevel(firstLevel);
        _levelManager.setCurrentLevelId(1);
    }

    void Game::_createNewPlayers(const std::vector<int>& ids, size_t &currentNbPlayerEntities)
    {
        constexpr uint16_t playerPosX = 200;
        constexpr uint16_t playerPosY = 540;

        for (auto id : ids) {
            if (_playerIdEntityMap.contains(id)) {
                continue;
            }
            auto player = _ecs.createEntity();
            player->addComponent<ecs::Health>(cmn::playerHealth);
            player->addComponent<ecs::Position>(playerPosX, playerPosY);
            player->addComponent<ecs::InputPlayer>();
            player->addComponent<ecs::Collision>(ecs::TypeCollision::PLAYER, cmn::playerWidth, cmn::playerHeight);
            player->addComponent<ecs::Shoot>(cmn::playerDamage, cmn::playerCoolDown);
            _playerIdEntityMap[id] = player->getId();
            _entityIdPlayerMap[player->getId()] = id;
            currentNbPlayerEntities++;
        }

    }

//    void Game::_initEcsManager()
//    {
//
//
//        auto player = _ecs.createEntity();
//        player->addComponent<ecs::Health>(cmn::playerHealth);
//        player->addComponent<ecs::Position>(playerPosX, playerPosY);
//        player->addComponent<ecs::InputPlayer>();
//        player->addComponent<ecs::Collision>(ecs::TypeCollision::PLAYER, cmn::playerWidth, cmn::playerHeight);
//        player->addComponent<ecs::Shoot>(cmn::playerDamage, cmn::playerCoolDown);
//
//        _ecs.addSystem<ecs::DestroySystem>();
//        _ecs.addSystem<ecs::MovementSystem>();
//        _ecs.addSystem<ecs::CollisionSystem>();
//        _ecs.addSystem<ecs::ShootSystem>();
//        _ecs.addSystem<ecs::VelocitySystem>();
//        _ecs.addSystem<ecs::HealthSystem>();
//    }

}