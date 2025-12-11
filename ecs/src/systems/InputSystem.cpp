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
        inputPtr->setDown(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S));
        inputPtr->setUp(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Z));
        inputPtr->setLeft(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Q));
        inputPtr->setRight(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D));
        inputPtr->setSpacebar(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space));
    }
}
}