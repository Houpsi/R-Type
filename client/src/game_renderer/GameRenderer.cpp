/*
** EPITECH PROJECT, 2025
** R_Type
** File description:
** Game
*/

#include "GameRenderer.hpp"

#include "client/Client.hpp"
#include "constants/GameConstants.hpp"
#include "entity_factory/EntityFactory.hpp"
#include "components/Background.hpp"
#include "components/Sound.hpp"
#include "constants/GameConstants.hpp"
#include "constants/GameConstants.hpp"
#include "enums/Key.hpp"
#include "packet_disassembler/PacketDisassembler.hpp"
#include "packet_factory/PacketFactory.hpp"
#include "enums/LobbyType.hpp"
#include "packet_disassembler/PacketDisassembler.hpp"
#include "packet_factory/PacketFactory.hpp"
#include "systems/BackgroundSystem.hpp"
#include "systems/DestroySystem.hpp"
#include "systems/InputSystem.hpp"
#include "systems/PlayerAnimationSystem.hpp"
#include "systems/RenderSystem.hpp"
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
        }
    }

    void GameRenderer::_checkGamePlayerInput()
    {
        bool isPressed = false;
            for (uint8_t i = 0; i < static_cast<uint8_t>(cmn::Keys::None); ++i) {
            auto action = static_cast<cmn::Keys>(i);
            if (_inputManager.isActionTriggered(action)) {
                _sharedData->addUdpPacketToSend(
                    cmn::PacketFactory::createInputPacket(_playerId, action, cmn::KeyState::Pressed)
                );
                isPressed = true;
            }
        }
        if (!isPressed) {
            _sharedData->addUdpPacketToSend(
                cmn::PacketFactory::createInputPacket(_playerId, cmn::Keys::None, cmn::KeyState::Pressed));
        }
    }

    void GameRenderer::_checkMenuPlayerInput() const
    {
        const auto inputComp = _menuKeyboard->getComponent<ecs::InputPlayer>();

        if (_currentState == ClientState::Menu) {
            if (inputComp->getOne()) {
                std::cout << "Ask to start solo mode with id: "<< _playerId << std::endl;
                _sharedData->addTcpPacketToSend(cmn::PacketFactory::createSelectModePacket(cmn::LobbyType::Solo, _playerId));
            } else if (inputComp->getTwo()) {
                _sharedData->addTcpPacketToSend(cmn::PacketFactory::createSelectModePacket(cmn::LobbyType::Matchmaking, _playerId));
            } else if (inputComp->getThree()) {
                _sharedData->addTcpPacketToSend(cmn::PacketFactory::createSelectModePacket(cmn::LobbyType::Lobby, _playerId));
            }
        }
        if (_currentState == ClientState::Waiting) {
            if (inputComp->getFour()) {
                _sharedData->addTcpPacketToSend(cmn::PacketFactory::createLeaveLobbyPacket(_playerId));
            }
        }
    }

    void GameRenderer::_updateNetwork()
    {
        static const std::unordered_map<int, uint64_t> emptyMap{};

        if (_currentState == ClientState::InGame) {
            while (auto packet = _sharedData->getUdpReceivedPacket()) {
                if (auto data = cmn::PacketDisassembler::disassemble(packet.value())) {
                    _translator.translate(_gameEcs, data.value(), emptyMap);
                }
            }
        } else {
            if (auto packet = _sharedData->getTcpReceivedPacket()) {
                if (auto data = cmn::PacketDisassembler::disassemble(packet.value())) {
                    std::visit(
                        [this](auto &&arg) {
                            using T = std::decay_t<decltype(arg)>;
                            if constexpr (std::is_same_v<T, cmn::connectionData>) {
                                _playerId = arg.playerId;
                                std::cout << "player id: " << _playerId << "\n";
                            } else if constexpr (std::is_same_v<T, cmn::startGameData>) {
                                _currentState = ClientState::InGame;
                                std::cout << "starting game\n";
                            } else if constexpr (std::is_same_v<T, cmn::joinLobbyData>) {
                                _currentState = ClientState::Waiting;
                                std::cout << "joining lobby" << "\n";
                            } else if constexpr (std::is_same_v<T, cmn::errorTcpData>) {
                                //TODO: implement error id which are in constant
                            }
                        },
                        data.value());
                }
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
                    //TODO: same and maybe win ?
                    _window.close();
                    return;
            }
            elapsedTime = inputClock.getElapsedTime().asSeconds();
        }
        _window.close();
    }


}