/*
** EPITECH PROJECT, 2025
** R_Type
** File description:
** Game
*/

#include "Game.hpp"
#include "constants/GameConstants.hpp"
#include "components/collision/Collision.hpp"
#include "components/health/Health.hpp"
#include "components/inputPlayer/InputPlayer.hpp"
#include "components/position//Position.hpp"
#include "components/shoot/Shoot.hpp"
#include "components/enemy/Enemy.hpp"
#include "data_translator/DataTranslator.hpp"
#include "packet_factory/PacketFactory.hpp"
#include "systems/collision/CollisionSystem.hpp"
#include "systems/destroy/DestroySystem.hpp"
#include "systems/health/HealthSystem.hpp"
#include "systems/input/InputSystem.hpp"
#include "systems/movement/MovementSystem.hpp"
#include "systems/shoot/ShootSystem.hpp"
#include "systems/velocity/VelocitySystem.hpp"
#include <algorithm>
#include <random>
#include "packet_disassembler/PacketDisassembler.hpp"
#include "packet_data/PacketData.hpp"

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
        Level  const&currentLevel = _levelManager.getCurrentLevel();
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
            _sharedData->addUdpPacketToSend(cmn::PacketFactory::createDeleteEntityPacket(entity));
        }
    }

    void Game::_sendPositions()
    {
        for (auto &entity : _ecs.getEntitiesWithComponent<ecs::Position>()) {
            auto component = _ecs.getComponent<ecs::Position>(entity);
            std::pair<float, float> const position = { component.getX(), component.getY() };
            _sharedData->addUdpPacketToSend(
                cmn::PacketFactory::createPositionPacket(position, entity));
        }
    }

    void Game::_checkSpaceBar()
    {
        for (auto const &entity : _ecs.getEntitiesWithComponent<ecs::InputPlayer>()) {

            if (_ecs.entityHasComponent<ecs::Shoot, ecs::InputPlayer>(entity)) {
                auto input = _ecs.getComponent<ecs::InputPlayer>(entity);
                auto shoot = _ecs.getComponent<ecs::Shoot>(entity);

                shoot.setTimeSinceLastShot(shoot.getTimeSinceLastShot() + _ecs.getDeltaTime());

                if (input.getSpacebar()) {
                    if (shoot.getTimeSinceLastShot() >= shoot.getCooldown()) {
                        auto projectile = _ecs.createEntity();
                        auto positionCpn = _ecs.getComponent<ecs::Position>(entity);
                        auto collisionCpn = _ecs.getComponent<ecs::Collision>(entity);

                        shoot.setTimeSinceLastShot(0);

                        float const posX = positionCpn.getX() + collisionCpn.getHeight();
                        float const posY = _ecs.getComponent<ecs::Position>(entity).getY();
                        auto shootCpn = _ecs.getComponent<ecs::Shoot>(entity);

                        _ecs.addComponentToEntity(projectile, ecs::Position(posX, posY));
                        _ecs.addComponentToEntity(projectile, ecs::Velocity(
                            cmn::playerProjectileSpeed,
                            cmn::playerProjectileDirection
                        ));
                        _ecs.addComponentToEntity(projectile, ecs::Shoot(shootCpn.getDamage(), shootCpn.getCooldown()));
                        _ecs.addComponentToEntity(projectile, ecs::Collision(
                        ecs::TypeCollision::PLAYER_PROJECTILE,
                        cmn::playerProjectileCollisionWidth,
                        cmn::playerProjectileCollisionHeight
                        ));

                        std::pair<float, float> const position = {posX, posY};

                        _sharedData->addUdpPacketToSend(
                            cmn::PacketFactory::createNewEntityPacket(
                                cmn::EntityType::PlayerProjectile,
                                position,
                                projectile
                            )
                        );
                    }
                }
            }
        }
    }

    void Game::_createEnemy(Level const &currentLevel, sf::Clock &enemyClock, std::minstd_rand0 &generator)
    {
        if (enemyClock.getElapsedTime().asSeconds() > static_cast<float>(currentLevel.getEnemySpawnRate())) {
            enemyClock.restart();
            auto randNum = generator() % (cmn::monsterMaxSpawnPositionHeight);
            auto newEnemy = _ecs.createEntity();

            _ecs.addComponentToEntity(newEnemy, ecs::Position(cmn::monsterSpawnPositionWidth, randNum));
            _ecs.addComponentToEntity(newEnemy, ecs::Enemy());
            _ecs.addComponentToEntity(newEnemy, ecs::Health(cmn::monsterHealth));
            _ecs.addComponentToEntity(newEnemy, ecs::Collision(
                ecs::TypeCollision::ENEMY,
                cmn::monsterCollisionWidth,
                cmn::monsterCollisionHeight));

            std::pair<float, float> const position = {cmn::monsterSpawnPositionWidth, randNum};
            _sharedData->addUdpPacketToSend(
                cmn::PacketFactory::createNewEntityPacket(
                    cmn::EntityType::Monster,
                    position,
                    newEnemy
                )
            );
        }
    }

    void Game::_sendPlayerEntities()
    {
        for (auto &entity : _ecs.getEntitiesWithComponent<ecs::Position>()) {
            auto component = _ecs.getComponent<ecs::Position>(entity);
            std::pair<float, float> const pos = {component.getX(), component.getY()};

            _sharedData->addUdpPacketToSend(
                cmn::PacketFactory::createNewEntityPacket(
                    cmn::EntityType::Player,
                    pos,
                    entity
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
                if (_ecs.getComponent<ecs::InputPlayer>(entity).getReady()
                    && !_isIdAlreadyPresent(_entityIdPlayerMap[entity])) {
                    _readyPlayersId.push_back(_entityIdPlayerMap[entity]);
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
            auto player = _ecs.createEntity();
            _ecs.addComponentToEntity(player, ecs::Health(cmn::playerHealth));
            _ecs.addComponentToEntity(player, ecs::Position(playerPosX, playerPosY));
            _ecs.addComponentToEntity(player, ecs::InputPlayer());
            _ecs.addComponentToEntity(player, ecs::Collision(ecs::TypeCollision::PLAYER, cmn::playerWidth, cmn::playerHeight));
            _ecs.addComponentToEntity(player, ecs::Shoot(cmn::playerDamage, cmn::playerCoolDown));

            _playerIdEntityMap[id] = player;
            _entityIdPlayerMap[player] = id;
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