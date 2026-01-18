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
#include "components/Sound.hpp"
#include "enums/Key.hpp"
#include "systems/BackgroundSystem.hpp"
#include "systems/DestroySystem.hpp"
#include "systems/InputSystem.hpp"
#include "systems/PlayerAnimationSystem.hpp"
#include "systems/RenderSystem.hpp"
#include "systems/SoundSystem.hpp"
#include "systems/SpriteAnimationSystem.hpp"
#include "systems/VelocitySystem.hpp"
#include "packet_factory/PacketFactory.hpp"
#include "components/Score.hpp"
#include "systems/ScoreTextSystem.hpp"
#include <functional>

namespace client {

    GameRenderer::GameRenderer(const std::shared_ptr<cmn::SharedData> &data) : _sharedData(data)
    {
        sf::Vector2u const vector = sf::VideoMode::getDesktopMode().size;
        _window = sf::RenderWindow(sf::VideoMode({vector.x, vector.y}), "R-Type");
    }

    void GameRenderer::_initEcsSystem()
    {
        _ecs.addSystem<ecs::InputSystem>();
        _ecs.addSystem<ecs::SoundSystem>();
        _ecs.addSystem<ecs::PlayerAnimationSystem>();
        _ecs.addSystem<ecs::SpriteAnimationSystem>();
        _ecs.addSystem<ecs::ScoreTextSystem>();
        _ecs.addSystem<ecs::RenderSystem>(_window, _inputManager.getShaderName());
        _ecs.addSystem<ecs::DestroySystem>();
        _ecs.addSystem<ecs::VelocitySystem>();
        _ecs.addSystem<ecs::BackgroundSystem>();
    }

    void GameRenderer::_initKeyboard()
    {
        const auto keyboard = _ecs.createEntity(4);
        keyboard->addComponent<ecs::InputPlayer>();
        _keyboard = keyboard;
    }

    void GameRenderer::_initSound()
    {
        const auto sound = _ecs.createEntity(cmn::idEntityForMusic);
        _sound = sound;
        sound->addComponent<ecs::Sound>(cmn::idThemeMusic, true);
    }

    void GameRenderer::_initScore()
    {
        const auto scoreEntity = _ecs.createEntity(cmn::idEntityForScore);

        scoreEntity->addComponent<ecs::Position>(cmn::positionScoreX, cmn::positionScoreY);
        scoreEntity->addComponent<ecs::Score>();
        scoreEntity->addComponent<ecs::Text>(
            _ecs.getResourceManager().getFont(cmn::fontPath.data()),
            cmn::sizeScore
        );
    }

    void GameRenderer::_initBackground()
    {
        cmn::EntityFactory::createEntity(
            _ecs,
            cmn::EntityType::BackgroundStars,
            cmn::posZero.x, cmn::posZero.y,
            cmn::EntityFactory::Context::CLIENT,
            0, cmn::idBg1
        );

        cmn::EntityFactory::createEntity(
            _ecs,
            cmn::EntityType::BackgroundStars,
            cmn::posOne.x, cmn::posOne.y,
            cmn::EntityFactory::Context::CLIENT,
            0, cmn::idBg2
        );

        cmn::EntityFactory::createEntity(
            _ecs,
            cmn::EntityType::BackgroundPlanets,
            cmn::posZero.x, cmn::posZero.y,
            cmn::EntityFactory::Context::CLIENT,
            0, cmn::idStart1
        );

        cmn::EntityFactory::createEntity(
            _ecs,
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

    void GameRenderer::_checkPlayerInput()
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

    void GameRenderer::_updateNetwork()
    {
        static const std::unordered_map<int, uint64_t> emptyMap{};

        if (_isRunning) {
            while (auto data = _sharedData->getUdpReceivedPacket()) {
                _translator.translate(_ecs, data.value(), emptyMap);
            }
        } else {
            if (auto data = _sharedData->getTcpReceivedPacket()) {
                std::visit([this](auto &&arg)
                    {
                        using T = std::decay_t<decltype(arg)>;
                        if constexpr (std::is_same_v<T, cmn::connectionData>) {
                            _playerId = arg.playerId;
                        } else if constexpr (std::is_same_v<T, cmn::startGameData>) {
                            _isRunning = true;
                        }
                    }, data.value());
            }
        }
    }

    void GameRenderer::_updateLobby()
    {
        _checkPlayerInput();
    }

    void GameRenderer::_updateGame()
    {
        _checkPlayerInput();
    }

    void GameRenderer::run()
    {
        sf::Clock inputClock;
        constexpr float inputCooldown = 0.016F;
        float elapsedTime = 0;

        _initEcsSystem();
        _initBackground();
        _initKeyboard();
        _initSound();
        _initScore();
        while (_window.isOpen()) {
            const float deltaTime = _clock.restart().asSeconds();
            _updateNetwork();
            _handleEvents();
            if (_isRunning) {
                if (elapsedTime > inputCooldown) {
                    _updateGame();
                    inputClock.restart();
                }
            } else {
                _updateLobby();
            }
            _ecs.setDeltaTime(deltaTime);
            _ecs.updateSystems();
            elapsedTime = inputClock.getElapsedTime().asSeconds();
        }
        _window.close();
    }


}