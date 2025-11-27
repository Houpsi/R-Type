//
// Created by aleks on 27/11/2025.
//

#include "Game.hpp"

#include "Components/Health.hpp"
#include "Components/Position.hpp"
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
    sf::RenderWindow window(sf::VideoMode(static_cast<int>(100), static_cast<int>(100)), "SFML window");


    player->addComponent<Health>(100);
    player->addComponent<Position>(1, 2);
    player->addComponent<InputPlayer>(1);


    _ecs.addSystem<InputSystem>(false, false, false, false);
    _ecs.addSystem<MovementSystem>(1);
    _ecs.addSystem<RenderSystem>(window);

    while (window.isOpen()) {
        sf::Event event{};
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        _ecs.updateSystems();

    }
}
