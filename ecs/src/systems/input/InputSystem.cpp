/*
** EPITECH PROJECT, 2025
** R_Type
** File description:
** InputSystem
*/

#include "InputSystem.hpp"

namespace ecs {
void InputSystem::update(EcsManager & ecs) {
    for (auto& entity : ecs.getEntities()) {
        auto inputPtr = entity->getComponent<InputPlayer>();
        if (!inputPtr) {
            continue;
        }
        inputPtr->setDown(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)
                          || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down));
        inputPtr->setUp(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Z)
                        || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up));
        inputPtr->setLeft(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Q)
                          || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left));
        inputPtr->setRight(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)
                           || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right));
        inputPtr->setSpacebar(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space));
        inputPtr->setR(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::R));
    }
}
}