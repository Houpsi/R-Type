/*
** EPITECH PROJECT, 2025
** R_Type
** File description:
** Game
*/


#include "Game.hpp"

#include "Components/Enemy.hpp"
#include "Components/Health.hpp"
#include "Components/Position.hpp"
#include "Components/Sprite.hpp"
#include "Systems/InputSystem.hpp"
#include "Systems/MovementSystem.hpp"
#include "Systems/RenderSystem.hpp"

Game::Game() {
    _ecs = EcsManager();
}

Game::~Game() {

}

void Game::run() {
    auto player = _ecs.createEntity();
    auto enemy = _ecs.createEntity();
    sf::RenderWindow window(sf::VideoMode({1920, 1080}), "R-Type");
    sf::Clock clock;

    player->addComponent<Health>(100);
    player->addComponent<Position>(1, 2);
    player->addComponent<InputPlayer>();
    player->addComponent<Sprite>("./assets/r-typesheet30a.gif");

    enemy->addComponent<Health>(100);
    enemy->addComponent<Position>(100, 100);
    enemy->addComponent<Enemy>();
    enemy->addComponent<Sprite>("./assets/r-typesheet30a.gif");


    _ecs.addSystem<InputSystem>();
    _ecs.addSystem<MovementSystem>();
    _ecs.addSystem<RenderSystem>(window);

    while (window.isOpen()) {
        float dt = clock.restart().asSeconds();

        while (const std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>())
                window.close();
            // -------- TODO remove that later - Dev and testing purpose only
            if (const auto* keyEvent = event->getIf<sf::Event::KeyPressed>()) {
                if (keyEvent->code == sf::Keyboard::Key::K) {
                    auto newEnemy = _ecs.createEntity();
                    newEnemy->addComponent<Health>(100);
                    newEnemy->addComponent<Position>(200, 100);
                    newEnemy->addComponent<Enemy>();
                    newEnemy->addComponent<Sprite>("./assets/r-typesheet30a.gif");
                }
            }
            // --------
        }
        _ecs.setDeltaTime(dt);
        _ecs.updateSystems();
    }
}
