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
#include <random>

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

            std::optional<cmn::packetData> data = _sharedData->getUdpReceivedPacket();

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

        for (auto &entity : _ecs.getEntities()) {
            auto component = entity->getComponent<ecs::Position>();
            std::pair<float, float> const pos = {component->getX(), component->getY()};
            _sharedData->addTcpPacketToSend(cmn::PacketFactory::createNewEntityPacket(cmn::EntityType::Player, pos, entity->getId()));
        }

        _initEcsManager();

        Level  const&currentLevel = _levelManager.getCurrentLevel();
        sf::Clock clock;
        sf::Clock enemyClock;
        unsigned const seed = std::chrono::system_clock::now().time_since_epoch().count();
        std::minstd_rand0 generator(seed);

        while (true) {
            float const deltaTime = clock.restart().asSeconds();
            std::optional<cmn::packetData> data = _sharedData->getUdpReceivedPacket();

            if (data.has_value()) {
                cmn::DataTranslator::translate(_ecs, data.value(), _playerIdEntityMap);
            }

            if (enemyClock.getElapsedTime().asSeconds() > static_cast<float>(currentLevel.getEnemySpawnRate())) {
                enemyClock.restart();
                auto randNum = generator() % (cmn::monsterMaxSpawnPositionHeight);
                auto newEnemy = _ecs.createEntity();

                newEnemy->addComponent<ecs::Position>(cmn::monsterSpawnPositionWidth, randNum);
                newEnemy->addComponent<ecs::Enemy>();
                newEnemy->addComponent<ecs::Health>(cmn::monsterHealth);
                newEnemy->addComponent<ecs::Collision>(ecs::TypeCollision::ENEMY, cmn::monsterCollisionWidth, cmn::monsterCollisionHeight);
                std::pair<float, float> const position = {cmn::monsterSpawnPositionWidth, randNum};
                _sharedData->addUdpPacketToSend(cmn::PacketFactory::createNewEntityPacket(cmn::EntityType::Monster, position, newEnemy->getId()));
            }
            for (auto const &entity : _ecs.getEntitiesWithComponent<ecs::InputPlayer>()) {
                auto input = entity->getComponent<ecs::InputPlayer>();
                if (!entity->getComponent<ecs::Shoot>()) {
                    continue;
                }
                if (input) {
                    const auto shoot = entity->getComponent<ecs::Shoot>();
                    shoot->setTimeSinceLastShot(shoot->getTimeSinceLastShot() + _ecs.getDeltaTime());

                    if (input->getSpacebar()) {
                        if (shoot->getTimeSinceLastShot() >= shoot->getCooldown()) {
                            auto projectile = _ecs.createEntity();

                            shoot->setTimeSinceLastShot(0);
                            float const posX = entity->getComponent<ecs::Position>()->getX() + entity->getComponent<ecs::Collision>()->getHeight();
                            float const posY = entity->getComponent<ecs::Position>()->getY();
                            projectile->addComponent<ecs::Position>(posX, posY);
                            projectile->addComponent<ecs::Velocity>(cmn::playerProjectileSpeed, cmn::playerProjectileDirection);
                            projectile->addComponent<ecs::Shoot>(entity->getComponent<ecs::Shoot>()->getDamage(), entity->getComponent<ecs::Shoot>()->getCooldown());
                            projectile->addComponent<ecs::Collision>(ecs::TypeCollision::PLAYER_PROJECTILE, cmn::playerProjectileCollisionWidth, cmn::playerProjectileCollisionHeight);
                            std::pair<float, float> const position = {posX, posY};
                            _sharedData->addUdpPacketToSend(cmn::PacketFactory::createNewEntityPacket(cmn::EntityType::PlayerProjectile, position, projectile->getId()));
                        }
                    }
                }
            }
            for (auto &entity : _ecs.getEntitiesWithComponent<ecs::Position>()) {
                auto component = entity->getComponent<ecs::Position>();
                std::pair<float, float> const position = {component->getX(), component->getY()};
                _sharedData->addUdpPacketToSend(cmn::PacketFactory::createPositionPacket(position, entity->getId()));
            }
            for (auto &entity : _ecs.getEntitiesWithComponent<ecs::Destroy>()) {
                _sharedData->addUdpPacketToSend(cmn::PacketFactory::createDeleteEntityPacket(entity->getId()));
            }
            _ecs.setDeltaTime(deltaTime);
            _ecs.updateSystems();
        }
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

    void Game::_initEcsManager()
    {
        _ecs.addSystem<ecs::DestroySystem>();
        _ecs.addSystem<ecs::MovementSystem>();
        _ecs.addSystem<ecs::CollisionSystem>();
        _ecs.addSystem<ecs::ShootSystem>();
        _ecs.addSystem<ecs::VelocitySystem>();
        _ecs.addSystem<ecs::HealthSystem>();
    }

}