/*
** EPITECH PROJECT, 2025
** R_Type
** File description:
** Game
*/

#include "Game.hpp"
#include "components/Collision.hpp"
#include "components/InputPlayer.hpp"
#include "components/Position.hpp"
#include "components/Score.hpp"
#include "components/Text.hpp"
#include "components/Shoot.hpp"
#include "components/Sound.hpp"
#include "constants/GameConstants.hpp"
#include "data_translator/DataTranslator.hpp"
#include "entity_factory/EntityFactory.hpp"
#include "enums/GameResultType.hpp"
#include "packet_data/PacketData.hpp"
#include "packet_disassembler/PacketDisassembler.hpp"
#include "packet_factory/PacketFactory.hpp"
#include "systems/CollisionSystem.hpp"
#include "systems/DestroySystem.hpp"
#include "systems/HealthSystem.hpp"
#include "systems/MovementSystem.hpp"
#include "systems/VelocitySystem.hpp"
#include <algorithm>
#include <random>
#include <thread>

namespace server {

     Game::Game(const std::shared_ptr<ServerSharedData> &data, const int lobbyId, const cmn::LobbyType lobbyType)
    : _sharedData(data), _lobbyId(lobbyId), _lobbyType(lobbyType)
     {
         try {
             ecs::EcsManager const manager {};
             _ecs = manager;
         } catch ([[maybe_unused]] std::exception &e) {
             throw std::exception();
         }
     }


    void Game::run()
    {
         //TODO: handle that private lobby can launch a new game inside the previous one
        _initLevels();
        _waitForPlayers();
        cmn::startGameData data = {};
        _sharedData->addLobbyTcpPacketToSend(_lobbyId, data);
        _sendPlayerEntities();
        _initEcsManager();
        _startGame();
        _sharedData->setLobbyState(_lobbyId, cmn::LobbyState::EndGame);
    }

    void Game::_checkBossDeath(Level &currentLevel, sf::Clock &enemyClock)
    {
        if (!currentLevel.hasBossSpawned()) {
            return;
        }
        if (_currentIdBoss != -1) {
            if (!_ecs.getEntityById(_currentIdBoss)) {
                _levelManager.changeToNextLevel();
                currentLevel = _levelManager.getCurrentLevel();
                _currentIdBoss = -1;
                enemyClock.restart();
            }
        }
    }

    void Game::_startGame()
    {
        Level &currentLevel = _levelManager.getCurrentLevel();
         // TODO: implement win
        sf::Clock fpsClock;
        sf::Clock clock;
        sf::Clock enemyClock;
         sf::Clock powerUpClock;
        unsigned const seed = std::chrono::system_clock::now().time_since_epoch().count();
        std::minstd_rand0 generator(seed);
        float elapsedTime = 0.0F;
        constexpr float frameTimer = 0.016F;

        while (_sharedData->getLobbyState(_lobbyId) == cmn::LobbyState::Running) {
            float const deltaTime = clock.restart().asSeconds();

            if (_levelManager.getGameFinished()) {
                _sendGameEndState(cmn::GameResultType::Win);
                break;
            }
            _handleDisconnectedPlayers();
            if (_playerIdEntityMap.empty()) {
                std::cout << "[Game] No players connected, ending game for lobby " << _lobbyId << "\n";
                break;
            }
            auto data = _sharedData->getLobbyUdpReceivedPacket(_lobbyId);
            if (data.has_value()) {
                cmn::DataTranslator::translate(_ecs, data.value(), _playerIdEntityMap);
            }
            _createBonus(currentLevel, powerUpClock, generator);
            _checkBossDeath(currentLevel, enemyClock);
            _createEnemy(currentLevel, enemyClock, generator);
            _checkSpaceBar();
            _enemyShoot();
            if (elapsedTime > frameTimer) {
                fpsClock.restart();
                _sendPositions();
            }
            _sendSound();
            _sendText();
            _sendDestroy();
            if (_areAllPlayersDead()) {
                _sendGameEndState(cmn::GameResultType::Lose);
                std::cout << "[Game] All players are dead, game over for lobby " << _lobbyId << "\n";
                break;
            }
            _ecs.setDeltaTime(deltaTime);
            _ecs.updateSystems();
            elapsedTime = fpsClock.getElapsedTime().asSeconds();
        }
    }

       void Game::_handleDisconnectedPlayers()
    {
        std::vector<int> connectedPlayers = _sharedData->getLobbyPlayers(_lobbyId);

        for (auto it = _playerIdEntityMap.begin(); it != _playerIdEntityMap.end();) {
            int playerId = it->first;

            bool isConnected = std::ranges::any_of(connectedPlayers,
                [playerId](int id) { return id == playerId; });

            if (!isConnected) {
                std::cout << "[Game] Player " << playerId << " disconnected from lobby " << _lobbyId << ", removing from game\n";
                uint64_t entityId = it->second;
                auto entities = _ecs.getEntities();
                for (const auto& entity : entities) {
                    if (entity->getId() == entityId) {
                        entity->addComponent<ecs::Destroy>();
                        cmn::deleteEntityData deleteData = {static_cast<uint32_t>(entityId)};
                        _sharedData->addLobbyUdpPacketToSend(_lobbyId, deleteData);
                        break;
                    }
                }
                _entityIdPlayerMap.erase(entityId);
                it = _playerIdEntityMap.erase(it);
            } else {
                ++it;
            }
        }
    }

    void Game::_checkPlayerDeaths(const std::shared_ptr<ecs::Entity> &entity)
    {
         uint64_t entityId = entity->getId();
         if (!_entityIdPlayerMap.contains(entityId)) {
             return;
         }
         int playerId = _entityIdPlayerMap[entityId];
         if (std::ranges::find(_deadPlayersId, playerId) != _deadPlayersId.end()) {
             return;
         }
         std::cout << "[Game] Player " << playerId << " died in lobby " <<  _lobbyId << "\n";
         _deadPlayersId.push_back(playerId);
         cmn::playerDeathData deathData = {static_cast<uint32_t>(playerId)};
         _sharedData->addLobbyUdpPacketToSend(_lobbyId, deathData);
    }

    bool Game::_areAllPlayersDead() const
    {
        if (_playerIdEntityMap.empty()) {
            return true;
        }

        return _deadPlayersId.size() == _playerIdEntityMap.size();
    }

    void Game::_sendGameEndState(cmn::GameResultType type) const
    {
        cmn::gameResultData data = {static_cast<bool>(type)};
        _sharedData->addLobbyUdpPacketToSend(_lobbyId, data);
         std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        _sharedData->setLobbyState(_lobbyId, cmn::LobbyState::EndGame);
    }

    void Game::_sendDestroy()
    {
        for (auto &entity : _ecs.getEntitiesWithComponent<ecs::Destroy>()) {
            cmn::deleteEntityData data = {entity->getId()};
            _sharedData->addLobbyUdpPacketToSend(_lobbyId, data);
            if (entity->getComponent<ecs::InputPlayer>()) {
                _checkPlayerDeaths(entity);
            }
            _entityPos.erase(entity->getId());
        }
    }

    void Game::_sendSound() const
    {
         for (const auto &entity : _ecs.getEntitiesWithComponent<ecs::Sound>()) {
             uint8_t const soundId = static_cast<uint8_t>(entity->getComponent<ecs::Sound>()->getIdMusic());
             cmn::soundData data = {soundId};
             _sharedData->addLobbyUdpPacketToSend(_lobbyId, data);
             entity->removeComponent<ecs::Sound>();
         }
     }

    void Game::_sendText()
     {
         for (auto& entity : _ecs.getEntitiesWithComponent<ecs::Score>()) {
             auto score = entity->getComponent<ecs::Score>();

             if (!score) {
                 continue;
             }

             if (score->getScore() == _score) {
                 continue;
             }

             cmn::textData data = {entity->getId(), score->getScore()};
             _sharedData->addLobbyUdpPacketToSend(_lobbyId, data);
             _score = score->getScore();
         }
     }

    void Game::_sendPositions()
    {
        std::vector<uint32_t> ids;
        std::vector<float> posX;
        std::vector<float> posY;

        for (auto &entity : _ecs.getEntitiesWithComponent<ecs::Position>()) {
            auto component = entity->getComponent<ecs::Position>();
            auto realPos = std::make_pair(component->getX(), component->getY());
            uint32_t const entityId = entity->getId();
            if (_entityPos.contains(entityId)) {
                auto oldPos = _entityPos[entityId];
                if (oldPos == realPos) {
                    continue;
                }
                _entityPos[entityId] = realPos;
                ids.push_back(entityId);
                posX.push_back(realPos.first);
                posY.push_back(realPos.second);
                continue;
            }
            _entityPos[entityId] = std::make_pair(realPos.first, realPos.second);
            ids.push_back(entityId);
            posX.push_back(realPos.first);
            posY.push_back(realPos.second);
        }
        cmn::positionData data = {ids, posX, posY};
        _sharedData->addLobbyUdpPacketToSend(_lobbyId, data);
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
                         const auto positionCpn = entity->getComponent<ecs::Position>();
                         const auto collisionCpn = entity->getComponent<ecs::Collision>();

                         shoot->setTimeSinceLastShot(0);

                         float const posX = positionCpn->getX() + collisionCpn->getHeight();
                         float const posY = entity->getComponent<ecs::Position>()->getY();
                         auto shootCpn = entity->getComponent<ecs::Shoot>();

                         const auto projectile = cmn::EntityFactory::createEntity(_ecs,
                             cmn::EntityType::PlayerProjectile,
                             posX,
                             posY,
                             cmn::EntityFactory::Context::SERVER);

                        cmn::newEntityData data = {projectile->getId(), cmn::EntityType::PlayerProjectile, posX, posY};
                        _sharedData->addLobbyUdpPacketToSend(_lobbyId, data);
                    }
                }
            }
        }
    }

    void Game::_enemyShoot()
     {
         for (auto const &entity : _ecs.getEntitiesWithComponent<ecs::Shoot>())
         {
             const auto shoot = entity->getComponent<ecs::Shoot>();
             const auto collision= entity->getComponent<ecs::Collision>();

             if (!shoot && !collision) {
                 continue;
             }

             if (collision && collision->getTypeCollision() == ecs::ENEMY) {
                 auto posCpn = entity->getComponent<ecs::Position>();
                 shoot->setShootTimer(shoot->getShootTimer() + _ecs.getDeltaTime());

                 if (shoot->getShootTimer() >= shoot->getCooldown()) {
                     shoot->setShootTimer(0);

                     float posX = posCpn->getX() - collision->getWidth() - 10;
                     float posY = posCpn->getY() + 15;

                     auto projectile = cmn::EntityFactory::createEntity(_ecs,
                          cmn::EntityType::MonsterProjectile,
                          posX,
                          posY,
                          cmn::EntityFactory::Context::SERVER);

                     cmn::newEntityData data {
                         projectile->getId(),
                         cmn::EntityType::MonsterProjectile,
                         posX,
                         posY
                     };
                     _sharedData->addLobbyUdpPacketToSend(_lobbyId, data);
                     shoot->setTimeSinceLastShot(0);
                     shoot->setShootTimer(0.f);
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
            const auto newEnemy = cmn::EntityFactory::createEntity(_ecs,
                                cmn::EntityType::Boss1,
                                cmn::boss1SpawnPositionWidth, cmn::boss1SpawnPositionHeight,
                                cmn::EntityFactory::Context::SERVER, boss.second);


            cmn::newEntityData data = {newEnemy->getId(), cmn::EntityType::Boss1, cmn::boss1SpawnPositionWidth,
                cmn::boss1SpawnPositionHeight};

            _currentIdBoss = newEnemy->getId();
            _sharedData->addLobbyUdpPacketToSend(_lobbyId, data);
            currentLevel.setBossSpawned(true);
            return;
        }

        auto &waves = currentLevel.getWaves();
        int const waveId = currentLevel.getCurrentWaveId();

        if (waveId >= waves.size()) {
            return;
        }

        auto &[waveDuration, enemies] = waves[waveId];
        float const elapsed = enemyClock.getElapsedTime().asSeconds();

        for (auto &enemy : enemies) {
            if (elapsed - enemy.lastSpawnTime >= enemy.spawnRate) {
                const auto randNum = generator() % cmn::monsterMaxSpawnPositionHeight;
                const auto newEnemy =  cmn::EntityFactory::createEntity(_ecs,
                                cmn::EntityType::Plane,
                                cmn::monsterSpawnPositionWidth, static_cast<float>(randNum),
                                cmn::EntityFactory::Context::SERVER);


                std::pair<float, float> const position = {
                    cmn::monsterSpawnPositionWidth,
                    static_cast<float>(randNum)
                };

                cmn::newEntityData enemyData = {newEnemy->getId(), enemy.type, position.first, position.second};

                _sharedData->addLobbyUdpPacketToSend(_lobbyId, enemyData);
                enemy.lastSpawnTime = elapsed;
            }
        }

        if (elapsed >= static_cast<float>(waveDuration)) {
            currentLevel.nextWave();
            enemyClock.restart();
        }
    }

    void Game::_sendPlayerEntities()
    {
        for (const auto &entity : _ecs.getEntities()) {
            const auto component = entity->getComponent<ecs::Position>();
            std::pair<float, float> const pos = {component->getX(), component->getY()};
            cmn::newEntityData data = {entity->getId(), cmn::EntityType::Player, pos.first, pos.second};
            _sharedData->addLobbyUdpPacketToSend(_lobbyId, data);
        }
    }

    void Game::_waitForPlayers()
    {
        size_t currentNbPlayerEntities = 0;
        auto listPlayerIds = _sharedData->getLobbyPlayers(_lobbyId);

         if (_lobbyType != cmn::LobbyType::Lobby) {
             _createNewPlayers(_sharedData->getLobbyPlayers(_lobbyId), currentNbPlayerEntities);
             return;
         }
        while (_readyPlayersId.size() != listPlayerIds.size() &&
            _sharedData->getLobbyState(_lobbyId) == cmn::LobbyState::Waiting) {
            listPlayerIds = _sharedData->getLobbyPlayers(_lobbyId);
            if (listPlayerIds.empty()) {
                std::cout << "[Game] No players in lobby " << _lobbyId <<", cancelling game start\n";
                return;
            }

            if (currentNbPlayerEntities != listPlayerIds.size()) {
                _createNewPlayers(listPlayerIds, currentNbPlayerEntities);
            }

            auto data = _sharedData->getLobbyUdpReceivedPacket(_lobbyId);

            if (!data.has_value()) {
                std::this_thread::sleep_for(std::chrono::milliseconds(10));
                continue;
            }

            cmn::DataTranslator::translate(_ecs, data.value(), _playerIdEntityMap);

            auto entities = _ecs.getEntitiesWithComponent<ecs::InputPlayer>();

            for (const auto &entity : entities) {
                if (entity->getComponent<ecs::InputPlayer>()->getReady()
                    && !_isIdAlreadyPresent(_entityIdPlayerMap[entity->getId()])) {
                    _readyPlayersId.push_back(_entityIdPlayerMap[entity->getId()]);
                }
            }

            if (_readyPlayersId.size() == listPlayerIds.size() && !listPlayerIds.empty()) {
                std::cout << "[Game] All players ready! Starting game for lobby " << _lobbyId << std::endl;
                _sharedData->setLobbyState(_lobbyId, cmn::LobbyState::Running);
            }
        }
    }

    bool Game::_isIdAlreadyPresent(int playerId)
    {
        return std::ranges::any_of(
            _readyPlayersId,
            [playerId](const int id) { return id == playerId; }
        );
    }

    void Game::_initLevels()
    {
        _levelManager.loadLevelFromFolder();
        _levelManager.setCurrentLevelId(1);
    }

    void Game::_createNewPlayers(const std::vector<int>& ids, size_t &currentNbPlayerEntities)
    {

        for (auto id : ids) {
            constexpr uint16_t playerPosX = 200;
            constexpr uint16_t playerPosY = 540;
            if (_playerIdEntityMap.contains(id)) {
                continue;
            }
            const auto player =  cmn::EntityFactory::createEntity(_ecs,
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
        _ecs.addSystem<ecs::VelocitySystem>();
        _ecs.addSystem<ecs::HealthSystem>();

         auto scoreEntity = _ecs.createEntity(cmn::idEntityForScore);
         scoreEntity->addComponent<ecs::Position>(cmn::positionScoreX, cmn::positionScoreY);
         scoreEntity->addComponent<ecs::Collision>(ecs::TypeCollision::PLAYER, cmn::playerWidth, cmn::playerHeight);
         scoreEntity->addComponent<ecs::Text>(
             _ecs.getResourceManager().getFont(cmn::fontPath.data()),
             cmn::sizeScore
         );
         scoreEntity->addComponent<ecs::Score>();
    }


    void Game::_createBonus(Level &currentLevel, sf::Clock &bonusClock, std::minstd_rand0 &generator)
     {
         if (bonusClock.getElapsedTime().asSeconds() < _nextBonusSpawnDelay) {
             return;
         }
         auto randY = generator() % cmn::monsterMaxSpawnPositionHeight;
         auto newBonus = cmn::EntityFactory::createEntity(_ecs,
                             cmn::EntityType::PowerUp,
                             cmn::monsterSpawnPositionWidth,
                             static_cast<float>(randY),
                             cmn::EntityFactory::Context::SERVER);

         cmn::newEntityData bonusData = {
             newBonus->getId(),
             cmn::EntityType::PowerUp,
             cmn::monsterSpawnPositionWidth,
             static_cast<float>(randY)
         };

         _sharedData->addLobbyUdpPacketToSend(_lobbyId, bonusData);

         bonusClock.restart();
         _nextBonusSpawnDelay = currentLevel.getBonusSpawnRate() + (generator() % (static_cast<int>(currentLevel.getBonusSpawnRate()) + 1));
     }

}