/*
** EPITECH PROJECT, 2025
** R_Type
** File description:
** Game
*/

#include "Game.hpp"

void Game::run() {
    auto player = _ecs.createEntity();
    sf::RenderWindow window(sf::VideoMode({WINDOW_X, WINDOW_Y}), "R-Type");
    sf::Clock clock;
    sf::Clock enemyClock;
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::minstd_rand0 generator (seed);

    player->addComponent<ecs::Health>(100);
    player->addComponent<ecs::Position>(200, WINDOW_Y / 2);
    player->addComponent<ecs::InputPlayer>();
    player->addComponent<ecs::Sprite>("./assets/r-typesheet30a.gif");
    player->addComponent<ecs::Collision>(ecs::TypeCollision::PLAYER, 20, 50);
    player->addComponent<ecs::Sound>("./sound/shoot.wav");
    player->addComponent<ecs::Shoot>(50, 1);

    _ecs.addSystem<ecs::InputSystem>();
    _ecs.addSystem<ecs::MovementSystem>();
    _ecs.addSystem<ecs::CollisionSystem>();
    _ecs.addSystem<ecs::ShootSystem>();
    _ecs.addSystem<ecs::RenderSystem>(window);
    _ecs.addSystem<ecs::VelocitySystem>();

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
            newEnemy->addComponent<ecs::Health>(100);
            newEnemy->addComponent<ecs::Position>(2000, randNum);
            newEnemy->addComponent<ecs::Enemy>();
            newEnemy->addComponent<ecs::Sprite>("./assets/r-typesheet28.gif");
            newEnemy->addComponent<ecs::Collision>(ecs::TypeCollision::ENEMY, 10, 10);

        }
        // --------
        _ecs.setDeltaTime(deltaTime);
        _ecs.updateSystems();
    }
}
