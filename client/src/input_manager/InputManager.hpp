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

        bool isActionTriggered(cmn::Keys action) const;

    private:
        std::map<cmn::Keys, InputBinding> _bindings;

        void _initDefaultBindings();
        bool _checkGamepad(const InputBinding& bind) const;

        // Helpers pour convertir String <-> SFML Key
        sf::Keyboard::Key _stringToKey(const std::string& keyName) const;
    };
}
#endif// R_TYPE_INPUTMANAGER_HPP
