/*
** EPITECH PROJECT, 2026
** R_Type
** File description:
** InputManager
*/

#ifndef R_TYPE_INPUTMANAGER_HPP
#define R_TYPE_INPUTMANAGER_HPP

#include <map>
#include <string>
#include <iostream>
#include <SFML/Window.hpp>
#include <libconfig.h++>

#include "enums/Key.hpp"

namespace client {

    struct InputBinding {
        sf::Keyboard::Key key;
        sf::Keyboard::Key other_key;
        unsigned int joystickButton;
        bool isAxis;
        sf::Joystick::Axis axis;
        float axisThreshold;
    };

    class InputManager {
    public:
        InputManager();
        ~InputManager() = default;

        void loadConfig(const std::string& filePath);
        [[nodiscard]] bool isActionTriggered(cmn::Keys action) const;
        [[nodiscard]] std::string getShaderName() const;
    private:
        std::map<cmn::Keys, InputBinding> _bindings;
        void _initDefaultBindings();
        [[nodiscard]] bool _checkGamepad(const InputBinding& bind) const;
        [[nodiscard]] sf::Keyboard::Key _stringToKey(const std::string& keyName) ;
        std::string _shader;
    };
}
#endif// R_TYPE_INPUTMANAGER_HPP
