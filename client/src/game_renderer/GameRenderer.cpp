/*
** EPITECH PROJECT, 2025
** R_Type
** File description:
** Game
*/

#include "GameRenderer.hpp"

#include "client/Client.hpp"
#include "components/Background.hpp"
#include "enums/Key.hpp"
#include "systems/BackgroundSystem.hpp"
#include "systems/CollisionSystem.hpp"
#include "systems/DestroySystem.hpp"
#include "systems/InputSystem.hpp"
#include "systems/MovementSystem.hpp"
#include "systems/PlayerAnimationSystem.hpp"
#include "systems/RenderSystem.hpp"
#include "systems/SpriteAnimationSystem.hpp"
#include "systems/VelocitySystem.hpp"

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
        keyboard->addComponent<ecs::InputPlayer>();
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
        const auto pathFistBackground = std::string("./assets/bg-stars2.png");
        const auto pathSecondBackground = std::string("./assets/v.png");
        constexpr uint8_t firstId = 0;
        constexpr uint8_t secondId = 1;
        constexpr uint8_t thirdId = 2;
        constexpr uint8_t fourId = 3;

        const auto background = _ecs.createEntity(firstId);
        background->addComponent<ecs::Position>(posZero.x, posZero.y);
        background->addComponent<ecs::Velocity>(veloFirstBackground.x, veloFirstBackground.y);
        background->addComponent<ecs::Sprite>(_ecs.getResourceManager().getTexture(pathFistBackground), scale);
        background->addComponent<ecs::Background>(sizeFistBackground);

        const auto backgroundNext = _ecs.createEntity(secondId);
        backgroundNext->addComponent<ecs::Position>(posOne.x, posOne.y);
        backgroundNext->addComponent<ecs::Velocity>(veloFirstBackground.x, veloFirstBackground.y);
        backgroundNext->addComponent<ecs::Sprite>(_ecs.getResourceManager().getTexture(pathFistBackground), scale);
        backgroundNext->addComponent<ecs::Background>(sizeFistBackground);

        const auto start = _ecs.createEntity(thirdId);
        start->addComponent<ecs::Position>(posZero.x, posZero.y);
        start->addComponent<ecs::Velocity>(veloSecondBackground.x, veloSecondBackground.y);
        start->addComponent<ecs::Sprite>(_ecs.getResourceManager().getTexture(pathSecondBackground), scale);
        start->addComponent<ecs::Background>(sizeSecondBackground);
        const auto startNext = _ecs.createEntity(fourId);
        startNext->addComponent<ecs::Position>(posTwo.x, posTwo.y);
        startNext->addComponent<ecs::Velocity>(veloSecondBackground.x, veloSecondBackground.y);
        startNext->addComponent<ecs::Sprite>(_ecs.getResourceManager().getTexture(pathSecondBackground), scale);
        startNext->addComponent<ecs::Background>(sizeSecondBackground);
    }


    void GameRenderer::_handleEvents()
    {
        while (const std::optional event = _window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                _window.close();
            }
        }
    }

    void GameRenderer::_checkPlayerInput() const
    {
        static const std::array<
            std::pair<cmn::Keys, std::function<bool(const ecs::InputPlayer&)>>,
            6
        > bindings = {{
            { cmn::Keys::Up,       [](const auto& keyboard){ return keyboard.getUp(); } },
            { cmn::Keys::Down,     [](const auto& keyboard){ return keyboard.getDown(); } },
            { cmn::Keys::Left,     [](const auto& keyboard){ return keyboard.getLeft(); } },
            { cmn::Keys::Right,    [](const auto& keyboard){ return keyboard.getRight(); } },
            { cmn::Keys::Space,    [](const auto& keyboard){ return keyboard.getSpacebar(); } },
            {cmn::Keys::R,         [](const auto& keyboard){ return keyboard.getReady(); } },
        }};

        const auto inputComp = _keyboard->getComponent<ecs::InputPlayer>();

        for (const auto& [key, check] : bindings) {
            if (check(*inputComp)) {
                cmn::packetData data{};
                cmn::inputPacket input{};

                data.packetId = 0;
                input.key = static_cast<uint8_t>(key);
                input.keyState = 1;
                input.playerId = _playerId;
                data.content = input;
                _sharedData->addUdpPacketToSend(data);
            }
        }
    }

    void GameRenderer::_updateNetwork()
    {
        static const std::unordered_map<int, uint64_t> emptyMap{};

        if (_isRunning) {
            while (auto packet = _sharedData->getUdpReceivedPacket()) {
                _translator.translate(_ecs, *packet, emptyMap);
            }
        } else {
            if (auto packet = _sharedData->getTcpReceivedPacket()) {
                std::visit([this](auto &&arg) {
                    using T = std::decay_t<decltype(arg)>;

                    if constexpr (std::is_same_v<T, cmn::connectionPacket>) {
                        _playerId = arg.playerId;
                    } else if constexpr (std::is_same_v<T, cmn::startGamePacket>) {
                        _isRunning = true;
                    }
                }, packet->content);
            }
        }
    }

    void GameRenderer::_updateLobby() const
    {
        _checkPlayerInput();
    }

    void GameRenderer::_updateGame() const
    {
        _checkPlayerInput();
    }

    void GameRenderer::run()
    {
        _initEcsSystem();
        _initBackground();
        _initKeyboard();

        while (_window.isOpen()) {
            const float deltaTime = clock.restart().asSeconds();
            _updateNetwork();
            _handleEvents();
            if (_isRunning) {
                _updateGame();
            } else {
                _updateLobby();
            }
            _ecs.setDeltaTime(deltaTime);
            _ecs.updateSystems();
        }
        _window.close();
    }


}