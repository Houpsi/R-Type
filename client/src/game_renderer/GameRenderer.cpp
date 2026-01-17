/*
** EPITECH PROJECT, 2025
** R_Type
** File description:
** Game
*/

#include "GameRenderer.hpp"

#include "client/Client.hpp"
#include "components/Destroy.hpp"
#include "components/Score.hpp"
#include "components/Sound.hpp"
#include "constants/GameConstants.hpp"
#include "constants/NetworkConstants.hpp"
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
#include "systems/ScoreTextSystem.hpp"
#include "systems/SoundSystem.hpp"
#include "systems/SpriteAnimationSystem.hpp"
#include "systems/VelocitySystem.hpp"
#include <functional>

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
        _gameEcs.addSystem<ecs::ScoreTextSystem>();

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

    void GameRenderer::_initScore()
    {
        const auto scoreEntity = _gameEcs.createEntity(cmn::idEntityForScore);

        scoreEntity->addComponent<ecs::Position>(cmn::positionScoreX, cmn::positionScoreY);
        scoreEntity->addComponent<ecs::Score>();
        scoreEntity->addComponent<ecs::Text>(
            _gameEcs.getResourceManager().getFont(cmn::fontPath.data()),
            cmn::sizeScore
        );
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
                if (_currentState == ClientState::EnteringLobbyCode) {
                    _handleCodeInput(*keyPressed);
                }
                else if (keyPressed->scancode == sf::Keyboard::Scancode::Escape) {
                    _window.close();
                }
            }
        }
    }

    void GameRenderer::_handleCodeInput(const sf::Event::KeyPressed& keyEvent)
    {
        if (keyEvent.scancode == sf::Keyboard::Scancode::Escape) {
            std::cout << "[LOBBY] Code entry cancelled\n";
            _lobbyCodeInput.clear();
            _currentState = ClientState::Menu;
            return;
        }
        if (keyEvent.scancode == sf::Keyboard::Scancode::Enter) {
            if (!_lobbyCodeInput.empty()) {
                uint32_t code = std::stoul(_lobbyCodeInput);
                std::cout << "[LOBBY] Joining lobby with code: " << code << "\n";
                cmn::requestJoinLobbyData data{_playerId, code};
                _sharedData->addTcpPacketToSend(data);
                _lobbyCodeInput.clear();
                _currentState = ClientState::Menu;
            }
            return;
        }
        if (keyEvent.scancode == sf::Keyboard::Scancode::Backspace) {
            if (!_lobbyCodeInput.empty()) {
                _lobbyCodeInput.pop_back();
            }
            return;
        }
        if (_lobbyCodeInput.length() < MAX_CODE_LENGTH) {
            static const std::map<sf::Keyboard::Scancode, char> numKeys = {
                {sf::Keyboard::Scancode::Num0, '0'},
                {sf::Keyboard::Scancode::Num1, '1'},
                {sf::Keyboard::Scancode::Num2, '2'},
                {sf::Keyboard::Scancode::Num3, '3'},
                {sf::Keyboard::Scancode::Num4, '4'},
                {sf::Keyboard::Scancode::Num5, '5'},
                {sf::Keyboard::Scancode::Num6, '6'},
                {sf::Keyboard::Scancode::Num7, '7'},
                {sf::Keyboard::Scancode::Num8, '8'},
                {sf::Keyboard::Scancode::Num9, '9'},
                {sf::Keyboard::Scancode::Numpad0, '0'},
                {sf::Keyboard::Scancode::Numpad1, '1'},
                {sf::Keyboard::Scancode::Numpad2, '2'},
                {sf::Keyboard::Scancode::Numpad3, '3'},
                {sf::Keyboard::Scancode::Numpad4, '4'},
                {sf::Keyboard::Scancode::Numpad5, '5'},
                {sf::Keyboard::Scancode::Numpad6, '6'},
                {sf::Keyboard::Scancode::Numpad7, '7'},
                {sf::Keyboard::Scancode::Numpad8, '8'},
                {sf::Keyboard::Scancode::Numpad9, '9'}
            };
            auto it = numKeys.find(keyEvent.scancode);
            if (it != numKeys.end()) {
                _lobbyCodeInput += it->second;
                std::cout << "[LOBBY] Current code: " << _lobbyCodeInput << "\n";
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


    void GameRenderer::_checkMenuPlayerInput()
    {
        std::vector<std::pair<cmn::Keys, std::function<void()>>> menuActions;

        if (_currentState == ClientState::Menu) {
            menuActions = {
                {cmn::Keys::MenuSolo, [this]() {
                    std::cout << "[MENU] Starting solo mode with id: " << _playerId << '\n';
                    cmn::selectModeData data = {cmn::LobbyType::Solo, _playerId};
                    _sharedData->addTcpPacketToSend(data);
                }},
                {cmn::Keys::MenuMatchmaking, [this]() {
                    std::cout << "[MENU] Starting matchmaking mode with id: " << _playerId << '\n';
                    cmn::selectModeData data = {cmn::LobbyType::Matchmaking, _playerId};
                    _sharedData->addTcpPacketToSend(data);
                }},
                {cmn::Keys::MenuLobby, [this]() {
                    std::cout << "[MENU] Creating lobby with id: " << _playerId << '\n';
                    cmn::selectModeData data = {cmn::LobbyType::Lobby, _playerId};
                    _sharedData->addTcpPacketToSend(data);
                }},
                {cmn::Keys::MenuJoinLobby, [this]() {
                    std::cout << "[MENU] Entering lobby code entry mode\n";
                    _lobbyCodeInput.clear();
                    _currentState = ClientState::EnteringLobbyCode;
                }}
            };
        }
        else if (_currentState == ClientState::Waiting) {
            menuActions = {
                {cmn::Keys::MenuLeave, [this]() {
                    std::cout << "[MENU] Leaving lobby with id: " << _playerId << '\n';
                    cmn::leaveLobbyData data = {_playerId};
                    _sharedData->addTcpPacketToSend(data);
                }}
            };
        }

        for (const auto& [key, action] : menuActions) {
            bool const currentPressed = _inputManager.isActionTriggered(key);
            bool const alreadyPressed = _previousMenuInputs[key];

            if (currentPressed && !alreadyPressed) {
                action();
            }
            _previousMenuInputs[key] = currentPressed;
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
                            std::cout << "[SYSTEM] Lobby code is: " << data.lobbyCode << "\n";
                        }
                    } else if constexpr (std::is_same_v<T, cmn::errorTcpData>) {
                        cmn::errorTcpData data = arg;
                        if (data.errorId == cmn::noExistentLobbyError) {
                            std::cout << "no lobby exist" << std::endl;
                        } else if (data.errorId == cmn::noWaitingLobby) {
                            std::cout << "no waiting lobby" << std::endl;
                        } else if (data.errorId == cmn::fullLobbyError) {
                            std::cout << "full lobby" << std::endl;
                        }

                    }
                },data.value());
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
        _previousInputs.clear();
        _previousMenuInputs.clear();
        _lobbyCodeInput.clear();

        while (_sharedData->getUdpReceivedPacket()) {}
        while (_sharedData->getTcpReceivedPacket()) {}

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
        _initScore();
        while (_window.isOpen() && _sharedData->isGameRunning()) {
            const float deltaTime = _clock.restart().asSeconds();
            _updateNetwork();
            _handleEvents();
            switch (_currentState) {
                case ClientState::Menu:
                    _updateMenu(inputClock, elapsedTime, deltaTime);
                    break;
                case ClientState::EnteringLobbyCode:
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