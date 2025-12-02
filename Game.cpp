/*
** EPITECH PROJECT, 2025
** R_Type
** File description:
** Game
*/


#include "Game.hpp"
#include "components/Enemy.hpp"
#include "components/Health.hpp"
#include "components/Position.hpp"
#include "components/Sprite.hpp"
#include "systems/InputSystem.hpp"
#include "systems/MovementSystem.hpp"
#include "systems/RenderSystem.hpp"

void Game::run() {
    auto player = _ecs.createEntity();
    sf::RenderWindow window(sf::VideoMode({WINDOW_X, WINDOW_Y}), "R-Type");
    sf::Clock clock;
    sf::Clock enemyClock;
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::minstd_rand0 generator (seed);

    player->addComponent<ECS::Health>(100);
    player->addComponent<ECS::Position>(200, WINDOW_Y / 2);
    player->addComponent<ECS::InputPlayer>();
    player->addComponent<ECS::Sprite>("./assets/r-typesheet30a.gif");

    _ecs.addSystem<ECS::InputSystem>();
    _ecs.addSystem<ECS::MovementSystem>();
    _ecs.addSystem<ECS::RenderSystem>(window);

    while (window.isOpen()) {
        float const deltaTime = clock.restart().asSeconds();

        while (const std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }
        }
        // -------- TODO remove that later - Dev and testing purpose only
        if (enemyClock.getElapsedTime().asSeconds() > 1) {
            enemyClock.restart();
            int const randNum = generator() % (WINDOW_Y + 1);
            auto newEnemy = _ecs.createEntity();
            newEnemy->addComponent<ECS::Health>(100);
            newEnemy->addComponent<ECS::Position>(2000, randNum);
            newEnemy->addComponent<ECS::Enemy>();
            newEnemy->addComponent<ECS::Sprite>("./assets/r-typesheet28.gif");
        }
        // --------
        _ecs.setDeltaTime(deltaTime);
        _ecs.updateSystems();
    }
}
