/*
** EPITECH PROJECT, 2025
** R_Type
** File description:
** Game
*/

#include "GameRenderer.hpp"

#include "client/Client.hpp"
#include "components/background/Background.hpp"
#include "enums/Key.hpp"
#include "systems/background/BackgroundSystem.hpp"
#include "systems/collision/CollisionSystem.hpp"
#include "systems/destroy/DestroySystem.hpp"
#include "systems/input/InputSystem.hpp"
#include "systems/movement/MovementSystem.hpp"
#include "systems/playerAnimation/PlayerAnimationSystem.hpp"
#include "systems/render/RenderSystem.hpp"
#include "systems/spriteAnimation/SpriteAnimationSystem.hpp"
#include "systems/velocity/VelocitySystem.hpp"
#include "packet_factory/PacketFactory.hpp"
#include "packet_disassembler/PacketDisassembler.hpp"

#include <functional>

namespace client {

    GameRenderer::GameRenderer(const std::shared_ptr<cmn::SharedData> &data) : _sharedData(data)
    {
        sf::Vector2u const vector = sf::VideoMode::getDesktopMode().size;
        _window = sf::RenderWindow(sf::VideoMode({vector.x, vector.y}), "R-Type");
    }

    void GameRenderer::_initEcsSystem()
    {
        _ecs.initComponents();
        _ecs.addSystem<ecs::InputSystem>();
        _ecs.addSystem<ecs::PlayerAnimationSystem>();
        _ecs.addSystem<ecs::SpriteAnimationSystem>();
        _ecs.addSystem<ecs::RenderSystem>(_window);
        _ecs.addSystem<ecs::DestroySystem>();
        _ecs.addSystem<ecs::VelocitySystem>();
        _ecs.addSystem<ecs::BackgroundSystem>();
    }

    void GameRenderer::_initKeyboard()
    {
        const auto keyboard = _ecs.createEntity(4);
        _ecs.addComponentToEntity(keyboard, ecs::InputPlayer());
        _keyboard = keyboard;
    }

    void GameRenderer::_initBackground()
    {
        constexpr sf::Vector2f scale(1.0F, 1.0F);
        constexpr sf::Vector2f posZero(0.0F, 0.0F);
        constexpr sf::Vector2f posOne(1920, 0);
        constexpr sf::Vector2f posTwo(3840, 0);
        constexpr sf::Vector2f veloFirstBackground(10.0F, 0.5F);
        constexpr sf::Vector2f veloSecondBackground(20.0F, 0.5F);
        constexpr int sizeFistBackground = 1920;
        constexpr int sizeSecondBackground = 3840;
        const auto pathFistBackground = std::string("./assets/bg-stars.png");
        const auto pathSecondBackground = std::string("./assets/planets_background.png");
        constexpr uint8_t firstId = 0;
        constexpr uint8_t secondId = 1;
        constexpr uint8_t thirdId = 2;
        constexpr uint8_t fourId = 3;

        const auto background = _ecs.createEntity(firstId);
        _ecs.addComponentToEntity(background, ecs::Position(posZero.x, posZero.y));
        _ecs.addComponentToEntity(background, ecs::Velocity(veloFirstBackground.x, veloFirstBackground.y));
        _ecs.addComponentToEntity(background, ecs::Sprite(_ecs.getResourceManager().getTexture(pathFistBackground), scale));
        _ecs.addComponentToEntity(background, ecs::Background(sizeFistBackground));


        const auto backgroundNext = _ecs.createEntity(secondId);
        _ecs.addComponentToEntity(backgroundNext, ecs::Position(posOne.x, posOne.y));
        _ecs.addComponentToEntity(backgroundNext, ecs::Velocity(veloFirstBackground.x, veloFirstBackground.y));
        _ecs.addComponentToEntity(backgroundNext, ecs::Sprite(_ecs.getResourceManager().getTexture(pathFistBackground), scale));
        _ecs.addComponentToEntity(backgroundNext, ecs::Background(sizeSecondBackground));

        const auto start = _ecs.createEntity(thirdId);
        _ecs.addComponentToEntity(start, ecs::Position(posZero.x, posZero.y));
        _ecs.addComponentToEntity(start, ecs::Velocity(veloSecondBackground.x, veloSecondBackground.y));
        _ecs.addComponentToEntity(start, ecs::Sprite(_ecs.getResourceManager().getTexture(pathSecondBackground), scale));
        _ecs.addComponentToEntity(start, ecs::Background(sizeFistBackground));

        const auto startNext = _ecs.createEntity(fourId);
        _ecs.addComponentToEntity(startNext, ecs::Position(posTwo.x, posTwo.y));
        _ecs.addComponentToEntity(startNext, ecs::Velocity(veloSecondBackground.x, veloSecondBackground.y));
        _ecs.addComponentToEntity(startNext, ecs::Sprite(_ecs.getResourceManager().getTexture(pathSecondBackground), scale));
        _ecs.addComponentToEntity(startNext, ecs::Background(sizeFistBackground));
    }


    void GameRenderer::_handleEvents()
    {
        while (const std::optional event = _window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                _window.close();
            }
        }
    }

    void GameRenderer::_checkPlayerInput()
    {
        static const std::array<
            std::pair<cmn::Keys, std::function<bool(const ecs::InputPlayer&)>>, 6
        > bindings = {{
            { cmn::Keys::Up,       [](const auto& keyboard){ return keyboard.getUp(); } },
            { cmn::Keys::Down,     [](const auto& keyboard){ return keyboard.getDown(); } },
            { cmn::Keys::Left,     [](const auto& keyboard){ return keyboard.getLeft(); } },
            { cmn::Keys::Right,    [](const auto& keyboard){ return keyboard.getRight(); } },
            { cmn::Keys::Space,    [](const auto& keyboard){ return keyboard.getSpacebar(); } },
            { cmn::Keys::R,         [](const auto& keyboard){ return keyboard.getReady(); } },
        }};

        const auto inputComp = _ecs.getComponent<ecs::InputPlayer>(_keyboard);

        bool isPressed = false;
        for (const auto& [key, check] : bindings) {
            if (check(inputComp)) {
                _sharedData->addUdpPacketToSend(cmn::PacketFactory::createInputPacket(_playerId, key, cmn::KeyState::Pressed));
                isPressed = true;
            }
        }
        if (!isPressed) {
            _sharedData->addUdpPacketToSend(
                cmn::PacketFactory::createInputPacket(_playerId, cmn::Keys::None, cmn::KeyState::Pressed));
        }
    }

    void GameRenderer::_updateNetwork()
    {
        static const std::unordered_map<int, uint64_t> emptyMap{};

        if (_isRunning) {
            while (auto packet = _sharedData->getUdpReceivedPacket()) {
                if (auto data = cmn::PacketDisassembler::disassemble(packet.value())) {
                    _translator.translate(_ecs, data.value(), emptyMap);
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
                            } else if constexpr (std::is_same_v<T, cmn::startGameData>) {
                                _isRunning = true;
                            }
                        },
                        data.value());
                }
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
        while (_window.isOpen()) {
            const float deltaTime = _clock.restart().asSeconds();
            _updateNetwork();
            _handleEvents();
            if (_isRunning) {
                if (elapsedTime > inputCooldown) {
                    _updateGame();
                    inputClock.restart();
                    elapsedTime = 0;
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