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
        sf::Vector2f scale(1.0f, 1.0f);
        const auto background = _ecs.createEntity(0);
        background->addComponent<ecs::Position>(0, 0);
        background->addComponent<ecs::Velocity>(10, 0.5);
        background->addComponent<ecs::Sprite>(_ecs.getResourceManager().getTexture("./assets/bg-stars2.png"), scale);
        background->addComponent<ecs::Background>(1920);

        const auto backgroundNext = _ecs.createEntity(1);
        backgroundNext->addComponent<ecs::Position>(1920, 0);
        backgroundNext->addComponent<ecs::Velocity>(10, 0.5);
        backgroundNext->addComponent<ecs::Sprite>(_ecs.getResourceManager().getTexture("./assets/bg-stars2.png"), scale);
        backgroundNext->addComponent<ecs::Background>(1920);

        const auto start = _ecs.createEntity(2);
        start->addComponent<ecs::Position>(0, 0);
        start->addComponent<ecs::Velocity>(20, 0.5);
        start->addComponent<ecs::Sprite>(_ecs.getResourceManager().getTexture("./assets/v.png"), scale);
        start->addComponent<ecs::Background>(3840);
        auto startNext = _ecs.createEntity(3);
        startNext->addComponent<ecs::Position>(3840, 0);
        startNext->addComponent<ecs::Velocity>(20, 0.5);
        startNext->addComponent<ecs::Sprite>(_ecs.getResourceManager().getTexture("./assets/v.png"), scale);
        startNext->addComponent<ecs::Background>(3840);
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
            { cmn::Keys::Up,       [](const auto& c){ return c.getUp(); } },
            { cmn::Keys::Down,     [](const auto& c){ return c.getDown(); } },
            { cmn::Keys::Left,     [](const auto& c){ return c.getLeft(); } },
            { cmn::Keys::Right,    [](const auto& c){ return c.getRight(); } },
            { cmn::Keys::Space,    [](const auto& c){ return c.getSpacebar(); } },
            {cmn::Keys::R,         [](const auto& c){ return c.getReady(); } },
        }};

        const auto inputComp = _keyboard->getComponent<ecs::InputPlayer>();

        if (!inputComp) {
            return;
        }

        for (const auto& [key, check] : bindings) {
            if (check(*inputComp)) {
                cmn::packetData data{};
                cmn::inputPacket input{};

                data.packetId = 0;
                input.key = static_cast<uint8_t>(key);
                input.keyState = 1;

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

    void GameRenderer::_updateLobby()
    {
        _window.clear(sf::Color::Black);
        _window.display();
        _checkPlayerInput();
    }

    void GameRenderer::_updateGame(float) const {
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
                _updateGame(deltaTime);
            } else {
                _updateLobby();
            }
            _ecs.setDeltaTime(deltaTime);
            _ecs.updateSystems();
        }
        _window.close();
    }


}