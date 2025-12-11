/*
** EPITECH PROJECT, 2025
** R_Type
** File description:
** InputSystem
*/


#ifndef INPUTSYSTEM_HPP
    #define INPUTSYSTEM_HPP
#include <SFML/Window/Keyboard.hpp>
#include "System.hpp"
#include "../EcsManager.hpp"
#include "components/InputPlayer.hpp"

namespace ecs {
class InputSystem : public System {
  public:
    InputSystem() = default;
    void update(EcsManager &ecs) override;
};
}

#endif //INPUTSYSTEM_HPP