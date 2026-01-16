/*
** EPITECH PROJECT, 2025
** R_Type
** File description:
** Game
*/

#include "Game.hpp"
#include "components/Collision.hpp"
#include "components/Enemy.hpp"
#include "components/Health.hpp"
#include "components/InputPlayer.hpp"
#include "components/Position.hpp"
#include "components/Shoot.hpp"
#include "constants/GameConstants.hpp"
#include "data_translator/DataTranslator.hpp"
#include "entity_factory/EntityFactory.hpp"
#include "factory/EnemyProduct.hpp"
#include "packet_data/PacketData.hpp"
#include "packet_disassembler/PacketDisassembler.hpp"
#include "packet_factory/PacketFactory.hpp"
#include "systems/CollisionSystem.hpp"
#include "systems/DestroySystem.hpp"
#include "systems/HealthSystem.hpp"
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
        _waitForPlayers();
        _sharedData->addTcpPacketToSend(cmn::PacketFactory::createStartGamePacket());
        _sendPlayerEntities();
        _initEcsManager();
        _startGame();
    }

    [[noreturn]] void Game::_startGame()
    {
        Level &currentLevel = _levelManager.getCurrentLevel();
        sf::Clock fpsClock;
        sf::Clock clock;
        sf::Clock enemyClock;
        unsigned const seed = std::chrono::system_clock::now().time_since_epoch().count();
        std::minstd_rand0 generator(seed);
        float elapsedTime = 0.0F;
        constexpr float frameTimer = 0.016F;

        while (true) {
            float const deltaTime = clock.restart().asSeconds();
            std::optional<cmn::CustomPacket> packet = _sharedData->getUdpReceivedPacket();

            if (packet.has_value()) {
                std::optional<cmn::packetData> data = cmn::PacketDisassembler::disassemble(packet.value());
                if (data.has_value()) {
                    cmn::DataTranslator::translate(_ecs, data.value(), _playerIdEntityMap);
                }
            }
            _createEnemy(currentLevel, enemyClock, generator);
            _checkSpaceBar();
            if (elapsedTime > frameTimer) {
                fpsClock.restart();
                _sendPositions();
            }
            _sendDestroy();
            _ecs.setDeltaTime(deltaTime);
            _ecs.updateSystems();
            elapsedTime = fpsClock.getElapsedTime().asSeconds();
        }
    }

    void Game::_sendDestroy()
    {
        for (auto &entity : _ecs.getEntitiesWithComponent<ecs::Destroy>()) {
            _sharedData->addUdpPacketToSend(cmn::PacketFactory::createDeleteEntityPacket(entity->getId()));
        }
    }

    void Game::_sendPositions()
    {
        for (auto &entity : _ecs.getEntitiesWithComponent<ecs::Position>()) {
            auto component = entity->getComponent<ecs::Position>();
            std::pair<float, float> const position = { component->getX(), component->getY() };
            _sharedData->addUdpPacketToSend(
                cmn::PacketFactory::createPositionPacket(position, entity->getId()));
        }
    }

    void Game::_checkSpaceBar()
    {
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
                        auto positionCpn = entity->getComponent<ecs::Position>();
                        auto collisionCpn = entity->getComponent<ecs::Collision>();

                        shoot->setTimeSinceLastShot(0);

                        float const posX = positionCpn->getX() + collisionCpn->getHeight();
                        float const posY = entity->getComponent<ecs::Position>()->getY();
                        auto shootCpn = entity->getComponent<ecs::Shoot>();

                        auto projectile = cmn::EntityFactory::createEntity(_ecs,
                            cmn::EntityType::PlayerProjectile,
                            posX,
                            posY,
                            cmn::EntityFactory::Context::SERVER);

                        std::pair<float, float> const position = {posX, posY};

                        _sharedData->addUdpPacketToSend(
                            cmn::PacketFactory::createNewEntityPacket(
                                cmn::EntityType::PlayerProjectile,
                                position,
                                projectile->getId()
                            )
                        );
                    }
                }
            }
        }
    }

    void Game::_createEnemy(Level &currentLevel, sf::Clock &enemyClock, std::minstd_rand0 &generator)
{
    if (currentLevel.isFinished()) {
        if (currentLevel.hasBossSpawned()) {
            return;
        }

        auto boss = currentLevel.getBoss();
        auto newEnemy = cmn::EntityFactory::createEntity(_ecs,
                            cmn::EntityType::Boss1,
                            cmn::boss1SpawnPositionWidth, cmn::boss1SpawnPositionHeight,
                            cmn::EntityFactory::Context::SERVER, boss.second);


        std::pair<float, float> const position = { cmn::boss1SpawnPositionWidth, cmn::boss1SpawnPositionHeight };

        _sharedData->addUdpPacketToSend(
            cmn::PacketFactory::createNewEntityPacket(
                cmn::EntityType::Boss1,
                position,
                newEnemy->getId()
            )
        );
        currentLevel.setBossSpawned(true);
        return;
    }

    auto &waves = currentLevel.getWaves();
    int waveId = currentLevel.getCurrentWaveId();

    if (waveId >= waves.size())
        return;

    auto &[waveDuration, enemies] = waves[waveId];
    float elapsed = enemyClock.getElapsedTime().asSeconds();

    for (auto &enemy : enemies) {
        if (elapsed - enemy.lastSpawnTime >= enemy.spawnRate) {
            auto randNum = generator() % cmn::monsterMaxSpawnPositionHeight;
            auto newEnemy =  cmn::EntityFactory::createEntity(_ecs,
                            cmn::EntityType::Plane,
                            cmn::monsterSpawnPositionWidth, randNum,
                            cmn::EntityFactory::Context::SERVER);


            std::pair<float, float> const position = {
                cmn::monsterSpawnPositionWidth,
                (float)randNum
            };

            _sharedData->addUdpPacketToSend(
                cmn::PacketFactory::createNewEntityPacket(
                    enemy.type,
                    position,
                    newEnemy->getId()
                )
            );
            enemy.lastSpawnTime = elapsed;
        }
    }

    if (elapsed >= waveDuration) {
        currentLevel.nextWave();
        enemyClock.restart();
    }
}

    void Game::_sendPlayerEntities()
    {
        for (auto &entity : _ecs.getEntities()) {
            auto component = entity->getComponent<ecs::Position>();
            std::pair<float, float> const pos = {component->getX(), component->getY()};

            _sharedData->addUdpPacketToSend(
                cmn::PacketFactory::createNewEntityPacket(
                    cmn::EntityType::Player,
                    pos,
                    entity->getId()
                )
            );
        }
    }

    void Game::_waitForPlayers()
    {
        size_t currentNbPlayerEntities = 0;
        size_t playerListSize = _sharedData->getPlayerListSize();

        while ((_readyPlayersId.size() != playerListSize) || (playerListSize == 0)) {
            playerListSize = _sharedData->getPlayerListSize();
            if (currentNbPlayerEntities != playerListSize) {
                _createNewPlayers(_sharedData->getAllPlayerIds(), currentNbPlayerEntities);
            }

            std::optional<cmn::CustomPacket> packet = _sharedData->getUdpReceivedPacket();

            if (!packet.has_value()) {
                continue;
            }

            std::optional<cmn::packetData> data = cmn::PacketDisassembler::disassemble(packet.value());

            if (!data.has_value()) {
                continue;
            }
            cmn::DataTranslator::translate(_ecs, data.value(), _playerIdEntityMap);

            auto entities = _ecs.getEntitiesWithComponent<ecs::InputPlayer>();

            for (auto &entity : entities) {
                if (entity->getComponent<ecs::InputPlayer>()->getReady()
                    && !_isIdAlreadyPresent(_entityIdPlayerMap[entity->getId()])) {
                    _readyPlayersId.push_back(_entityIdPlayerMap[entity->getId()]);
                }
            }
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
        _levelManager.loadLevelFromFolder();
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
            auto player =  cmn::EntityFactory::createEntity(_ecs,
                            cmn::EntityType::Player,
                            playerPosX, playerPosY,
                            cmn::EntityFactory::Context::SERVER);

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