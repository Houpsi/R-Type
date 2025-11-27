//
// Created by aleks on 27/11/2025.
//

#ifndef BOOTSTRAP_INPUTSYSTEM_HPP
#define BOOTSTRAP_INPUTSYSTEM_HPP
#include <iostream>
#include <SFML/Window/Keyboard.hpp>

#include "System.hpp"
#include "../EcsManager.hpp"
#include "../Components/InputPlayer.hpp"
#include "SFML/System.hpp"


class InputSystem : public System {
    public:
    bool _up;
    bool _down;
    bool _left;
    bool _right;
    public:
    InputSystem(bool up, bool down, bool left, bool right) {
        _up = up;
        _down = down;
        _left = left;
        _right = right;
    }
    void update(EcsManager & ecs) override {
        for (auto& entity : ecs.getEntities()) {
            auto inputPtr = entity->getComponent<InputPlayer>();
            if (!inputPtr) continue;

            inputPtr->_up = sf::Keyboard::isKeyPressed(sf::Keyboard::W);
            inputPtr->_down = sf::Keyboard::isKeyPressed(sf::Keyboard::S);
            inputPtr->_left = sf::Keyboard::isKeyPressed(sf::Keyboard::A);
            inputPtr->_right = sf::Keyboard::isKeyPressed(sf::Keyboard::D);
            std::cout << inputPtr->_up << " " << inputPtr->_down << " " << inputPtr->_left << " " << inputPtr->_right << std::endl;
        }
    }
};


#endif //BOOTSTRAP_INPUTSYSTEM_HPP