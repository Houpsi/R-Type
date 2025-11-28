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
    sf::RenderWindow window(sf::VideoMode(static_cast<int>(1000), static_cast<int>(800)), "SFML window");
    sf::Clock clock;


    player->addComponent<Health>(100);
    player->addComponent<Position>(1, 2);
    player->addComponent<InputPlayer>();
    player->addComponent<Sprite>("image.png");

    enemy->addComponent<Health>(100);
    enemy->addComponent<Position>(100, 100);
    enemy->addComponent<Enemy>();
    enemy->addComponent<Sprite>("image.png");


    _ecs.addSystem<InputSystem>();
    _ecs.addSystem<MovementSystem>();
    _ecs.addSystem<RenderSystem>(window);

    while (window.isOpen()) {
        float dt = clock.restart().asSeconds();
        sf::Event event{};
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        _ecs.setDeltaTime(dt);
        _ecs.updateSystems();
    }
}
