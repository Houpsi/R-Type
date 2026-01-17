/*
** EPITECH PROJECT, 2025
** R_Type
** File description:
** Game
*/

#include "GameRenderer.hpp"

#include "client/Client.hpp"
#include "components/Destroy.hpp"
#include "components/Sound.hpp"
#include "constants/GameConstants.hpp"
#include "entity_factory/EntityFactory.hpp"
#include "enums/GameResultType.hpp"
#include "enums/Key.hpp"
#include "enums/LobbyType.hpp"
#include "packet_factory/PacketFactory.hpp"
#include "systems/BackgroundSystem.hpp"
#include "systems/DestroySystem.hpp"
#include "systems/InputSystem.hpp"
#include "systems/PlayerAnimationSystem.hpp"
#include "systems/RenderSystem.hpp"
#include "systems/SoundSystem.hpp"
#include "systems/SpriteAnimationSystem.hpp"
#include "systems/VelocitySystem.hpp"

namespace client {

    GameRenderer::GameRenderer(const std::shared_ptr<ClientSharedData> &data) : _sharedData(data)
    {
        sf::Vector2u const vector = sf::VideoMode::getDesktopMode().size;
        _window = sf::RenderWindow(sf::VideoMode({vector.x, vector.y}), "R-Type");
    }

    void GameRenderer::_initEcsSystem()
    {
        _gameEcs.addSystem<ecs::InputSystem>();
        _gameEcs.addSystem<ecs::SoundSystem>();
        _gameEcs.addSystem<ecs::PlayerAnimationSystem>();
        _gameEcs.addSystem<ecs::SpriteAnimationSystem>();
        _gameEcs.addSystem<ecs::RenderSystem>(_window, _inputManager.getShaderName());
        _gameEcs.addSystem<ecs::DestroySystem>();
        _gameEcs.addSystem<ecs::VelocitySystem>();
        _gameEcs.addSystem<ecs::BackgroundSystem>();

        _menuEcs.addSystem<ecs::InputSystem>();
        _menuEcs.addSystem<ecs::RenderSystem>(_window, _inputManager.getShaderName());
        _menuEcs.addSystem<ecs::DestroySystem>();
        _menuEcs.addSystem<ecs::BackgroundSystem>();
    }

    void GameRenderer::_initKeyboard()
    {
        const auto gameKeyboard = _gameEcs.createEntity(4);
        gameKeyboard->addComponent<ecs::InputPlayer>();
        _gameKeyboard = gameKeyboard;

        const auto menuKeyboard = _menuEcs.createEntity(0);
        menuKeyboard->addComponent<ecs::InputPlayer>();
        _menuKeyboard = menuKeyboard;
    }

    void GameRenderer::_initSound()
    {
        const auto sound = _gameEcs.createEntity(cmn::idEntityForMusic);
        _sound = sound;
        sound->addComponent<ecs::Sound>(cmn::idThemeMusic, true);
    }

    void GameRenderer::_initBackground()
    {
        cmn::EntityFactory::createEntity(
            _gameEcs,
            cmn::EntityType::BackgroundStars,
            cmn::posZero.x, cmn::posZero.y,
            cmn::EntityFactory::Context::CLIENT,
            0, cmn::idBg1
        );

        cmn::EntityFactory::createEntity(
            _gameEcs,
            cmn::EntityType::BackgroundStars,
            cmn::posOne.x, cmn::posOne.y,
            cmn::EntityFactory::Context::CLIENT,
            0, cmn::idBg2
        );

        cmn::EntityFactory::createEntity(
            _gameEcs,
            cmn::EntityType::BackgroundPlanets,
            cmn::posZero.x, cmn::posZero.y,
            cmn::EntityFactory::Context::CLIENT,
            0, cmn::idStart1
        );

        cmn::EntityFactory::createEntity(
            _gameEcs,
            cmn::EntityType::BackgroundPlanets,
            cmn::posTwo.x, cmn::posTwo.y,
            cmn::EntityFactory::Context::CLIENT,
            0, cmn::idStart2
        );
    }


    void GameRenderer::_handleEvents()
    {
        while (const std::optional event = _window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                _window.close();
            }
            else if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>())
            {
                if (keyPressed->scancode == sf::Keyboard::Scancode::Escape) {
                    _window.close();
                }
            }
        }
    }

    void GameRenderer::_checkGamePlayerInput()
    {
        for (uint8_t i = 0; i < static_cast<uint8_t>(cmn::Keys::None); ++i) {
            auto key = static_cast<cmn::Keys>(i);
            bool const currentPressed = _inputManager.isActionTriggered(key);
            bool const alreadyPressed = _previousInputs[key];
            if (currentPressed && !alreadyPressed) {
                cmn::inputData data = {_playerId, key, true};
                _sharedData->addUdpPacketToSend(data);
            }
            else if (!currentPressed && alreadyPressed) {
                cmn::inputData data = {_playerId, key, false};
                _sharedData->addUdpPacketToSend(data);
            }
            _previousInputs[key] = currentPressed;
        }
    }

    void GameRenderer::_checkMenuPlayerInput() const
    {
        // TODO: implement a way to choose to join lobby with code and write the code
        if (_currentState == ClientState::Menu) {
            if (_inputManager.isActionTriggered(cmn::Keys::MenuSolo)) {
                cmn::selectModeData data = {cmn::LobbyType::Solo, _playerId};
                _sharedData->addTcpPacketToSend(data);
            } else if (_inputManager.isActionTriggered(cmn::Keys::MenuMatchmaking)) {
                cmn::selectModeData data = {cmn::LobbyType::Matchmaking, _playerId};
                _sharedData->addTcpPacketToSend(data);
            } else if (_inputManager.isActionTriggered(cmn::Keys::MenuLobby)) {
                cmn::selectModeData data{cmn::LobbyType::Lobby, _playerId};
                _sharedData->addTcpPacketToSend(data);
            }
        } else if (_currentState == ClientState::Waiting) {
            if (_inputManager.isActionTriggered(cmn::Keys::MenuLeave)) {
                cmn::leaveLobbyData data = {_playerId};
                _sharedData->addTcpPacketToSend(data);
            }
        }
    }

    void GameRenderer::_updateNetwork()
    {
        static const std::unordered_map<int, uint64_t> emptyMap{};

        if (_currentState == ClientState::InGame) {
            while (auto data = _sharedData->getUdpReceivedPacket()) {
                std::visit([this](auto &&arg) {
                using T = std::decay_t<decltype(arg)>;
                if constexpr (std::is_same_v<T, cmn::gameResultData>) {
                    if (arg.gameResultType == static_cast<uint8_t>(cmn::GameResultType::Lose)) {
                        std::cout << "[GAME] Game lose" << std::endl;
                    } else {
                        std::cout << "[GAME] Game win" << std::endl;
                    }
                    _currentState = ClientState::GameOver;
                }
            }, data.value());
                _translator.translate(_gameEcs, data.value(), emptyMap);
            }
        } else {
            if (auto data = _sharedData->getTcpReceivedPacket()) {
                std::visit([this](auto &&arg) {
                            using T = std::decay_t<decltype(arg)>;
                            if constexpr (std::is_same_v<T, cmn::connectionData>) {
                                _playerId = arg.playerId;
                                std::cout << "[SYSTEM] your player id: " << _playerId << "\n";
                            } else if constexpr (std::is_same_v<T, cmn::startGameData>) {
                                _currentState = ClientState::InGame;
                                std::cout << "[GAME] starting game\n";
                            } else if constexpr (std::is_same_v<T, cmn::joinLobbyData>) {
                                _currentState = ClientState::Waiting;
                                std::cout << "[GAME]joining lobby" << "\n";
                                cmn::joinLobbyData data = arg;
                                if (data.lobbyType == cmn::LobbyType::Lobby) {
                                    std::cout << "[SYSTEM Lobby code is: " << data.lobbyCode << "\n";
                                }
                            } else if constexpr (std::is_same_v<T, cmn::errorTcpData>) {
                                //TODO: implement error id which are in constant
                                std::cout << "[SYSTEM] error" << "\n";
                            }
                        },
                        data.value());
            }
        }
    }

    void GameRenderer::_updateMenu(sf::Clock &inputClock, float elapsedTime, float deltaTime)
    {
        constexpr float inputCooldown = 0.1F;

        if (elapsedTime > inputCooldown) {
            _checkGamePlayerInput();
            inputClock.restart();
            elapsedTime = 0;
        }
        _checkMenuPlayerInput();
        _menuEcs.setDeltaTime(deltaTime);
        _menuEcs.updateSystems();
    }

    void GameRenderer::_updateGame(sf::Clock &inputClock, float elapsedTime, float deltaTime)
    {
        constexpr float inputCooldown = 0.016F;

        if (elapsedTime > inputCooldown) {
            _checkGamePlayerInput();
            inputClock.restart();
            elapsedTime = 0;
        }
        _gameEcs.setDeltaTime(deltaTime);
        _gameEcs.updateSystems();
    }

    void GameRenderer::_clearGameEntities()
    {
        auto entities = _gameEcs.getEntities();

        for (const auto& entity : entities) {
            uint64_t entityId = entity->getId();
            if (entityId != cmn::idEntityForMusic &&
                entityId != cmn::idBg1 &&
                entityId != cmn::idBg2 &&
                entityId != cmn::idStart1 &&
                entityId != cmn::idStart2 &&
                entityId != 4) {
                entity->addComponent<ecs::Destroy>();
                }
        }
        _gameEcs.updateSystems();
    }

    void GameRenderer::_resetGame()
    {
        std::cout << "[GameRenderer] Resetting game state\n";
        _clearGameEntities();
        _currentState = ClientState::Menu;
        while (_sharedData->getUdpReceivedPacket()) {
        }
        while (_sharedData->getTcpReceivedPacket()) {
        }
        if (_sound) {
            auto soundCpn = _sound->getComponent<ecs::Sound>();
            if (soundCpn) {
                soundCpn->setIsPlayed(false);
                soundCpn->setIsLoopping(true);
                soundCpn->setIsPlayed(true);
            }
        }
        std::cout << "[GameRenderer] Game reset complete\n";
    }

    void GameRenderer::run()
    {
        sf::Clock inputClock;
        float elapsedTime = 0;

        _initEcsSystem();
        _initBackground();
        _initKeyboard();
        _initSound();
        while (_window.isOpen() && _sharedData->isGameRunning()) {
            const float deltaTime = _clock.restart().asSeconds();
            _updateNetwork();
            _handleEvents();
            switch (_currentState) {
                case ClientState::Menu:
                    _updateMenu(inputClock, elapsedTime, deltaTime);
                    break;
                case ClientState::Waiting:
                    _updateMenu(inputClock, elapsedTime, deltaTime);
                    break;
                case ClientState::InGame:
                    _updateGame(inputClock, elapsedTime, deltaTime);
                    break;
                case ClientState::GameOver:
                    _window.clear();
                    _window.display();
                    std::this_thread::sleep_for(std::chrono::seconds(2));
                    _resetGame();
                    break;
            }
            elapsedTime = inputClock.getElapsedTime().asSeconds();
        }
        _window.close();
    }


}