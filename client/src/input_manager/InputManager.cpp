/*
** EPITECH PROJECT, 2026
** R_Type
** File description:
** InputManager
*/

#include "InputManager.hpp"
#include "constants/GameConstants.hpp"

namespace client {

    InputManager::InputManager()
    {
        _initDefaultBindings();
        try {
            loadConfig(static_cast<std::string>(cmn::configClientFile));
            std::cout << "[InputManager] Config loaded successfully." << '\n';
        } catch (const std::exception& e) {
            std::cerr << "[InputManager] Failed to load config: " << e.what() << ". Using defaults." << '\n';
        }
    }

    sf::Keyboard::Key InputManager::_stringToKey(const std::string& keyName)
    {
        static const std::map<std::string, sf::Keyboard::Key> keyMap = {
            {"A", sf::Keyboard::Key::A}, {"B", sf::Keyboard::Key::B}, {"C", sf::Keyboard::Key::C},
            {"D", sf::Keyboard::Key::D}, {"E", sf::Keyboard::Key::E}, {"F", sf::Keyboard::Key::F},
            {"G", sf::Keyboard::Key::G}, {"H", sf::Keyboard::Key::H}, {"I", sf::Keyboard::Key::I},
            {"J", sf::Keyboard::Key::J}, {"K", sf::Keyboard::Key::K}, {"L", sf::Keyboard::Key::L},
            {"M", sf::Keyboard::Key::M}, {"N", sf::Keyboard::Key::N}, {"O", sf::Keyboard::Key::O},
            {"P", sf::Keyboard::Key::P}, {"Q", sf::Keyboard::Key::Q}, {"R", sf::Keyboard::Key::R},
            {"S", sf::Keyboard::Key::S}, {"T", sf::Keyboard::Key::T}, {"U", sf::Keyboard::Key::U},
            {"V", sf::Keyboard::Key::V}, {"W", sf::Keyboard::Key::W}, {"X", sf::Keyboard::Key::X},
            {"Y", sf::Keyboard::Key::Y}, {"Z", sf::Keyboard::Key::Z},
            {"Up", sf::Keyboard::Key::Up},       {"Down", sf::Keyboard::Key::Down},
            {"Left", sf::Keyboard::Key::Left},   {"Right", sf::Keyboard::Key::Right},
            {"Space", sf::Keyboard::Key::Space}, {"Enter", sf::Keyboard::Key::Enter},
            {"Shift", sf::Keyboard::Key::LShift},{"Ctrl", sf::Keyboard::Key::LControl},
            {"Escape", sf::Keyboard::Key::Escape},
            {"Num1", sf::Keyboard::Key::Num1}, {"Num2", sf::Keyboard::Key::Num2},
            {"Num3", sf::Keyboard::Key::Num3},{"Num4", sf::Keyboard::Key::Num4},
            {"Num5", sf::Keyboard::Key::Num5}, {"Num6", sf::Keyboard::Key::Num6},
            {"Num7", sf::Keyboard::Key::Num5}, {"Num8", sf::Keyboard::Key::Num8},
            {"Num9", sf::Keyboard::Key::Num9}, {"Num0", sf::Keyboard::Key::Num0}
        };

        auto it = keyMap.find(keyName);
        if (it != keyMap.end()) {
            return it->second;
        }
        std::cerr << "[InputManager] Warning: Key '" << keyName << "' not found. Defaulting to Unknown." << '\n';
        return sf::Keyboard::Key::Unknown;
    }

    void InputManager::loadConfig(const std::string& filePath)
    {
        libconfig::Config cfg;

        try {
            cfg.readFile(filePath.c_str());
        } catch (const libconfig::FileIOException& fioex) {
            throw std::runtime_error("File I/O Error");
        } catch (const libconfig::ParseException& pex) {
            std::string const err = "Parse error at " + std::string(pex.getFile()) +
                ":" + std::to_string(pex.getLine()) + " - " + pex.getError();
            throw std::runtime_error(err);
        }

        try {
            const libconfig::Setting& root = cfg.getRoot();
            const libconfig::Setting& controls = root["controls"];

            auto bindKey = [&](const char* cfgName, cmn::Keys action) {
                std::string keyName;
                if (controls.lookupValue(cfgName, keyName)) {
                    _bindings[action].key = _stringToKey(keyName);
                }
            };

            bindKey("up",    cmn::Keys::Up);
            bindKey("down",  cmn::Keys::Down);
            bindKey("left",  cmn::Keys::Left);
            bindKey("right", cmn::Keys::Right);
            bindKey("shoot", cmn::Keys::Space);
            bindKey("ready", cmn::Keys::R);
            bindKey("menu_solo",         cmn::Keys::MenuSolo);
            bindKey("menu_matchmaking",  cmn::Keys::MenuMatchmaking);
            bindKey("menu_lobby",        cmn::Keys::MenuLobby);
            bindKey("menu_leave",        cmn::Keys::MenuLeave);
            bindKey("menu_join_lobby",        cmn::Keys::MenuJoinLobby);

            if (root.exists("shader")) {
                const libconfig::Setting& shader = root["shader"];
                if (shader.lookupValue("name", _shader)) {
                    std::cout << "[SHADER] : " << _shader << " load" <<  '\n';
                } else {
                    std::cout << "[SHADER] No shader load" << '\n';
                }
            }
        } catch (const libconfig::SettingNotFoundException& nfex) {
            std::cerr << "[InputManager] Setting not found in config file." << '\n';
        }
    }

    void InputManager::_initDefaultBindings()
    {
        _bindings[cmn::Keys::Up]    = {sf::Keyboard::Key::Z, sf::Keyboard::Key::Up,      0, true,  sf::Joystick::Axis::Y, -50.0f};
        _bindings[cmn::Keys::Down]  = {sf::Keyboard::Key::S, sf::Keyboard::Key::Down,      0, true,  sf::Joystick::Axis::Y,  50.0f};
        _bindings[cmn::Keys::Left]  = {sf::Keyboard::Key::Q,  sf::Keyboard::Key::Left,   0, true,  sf::Joystick::Axis::X, -50.0f};
        _bindings[cmn::Keys::Right] = {sf::Keyboard::Key::D, sf::Keyboard::Key::Right,    0, true,  sf::Joystick::Axis::X,  50.0f};
        _bindings[cmn::Keys::Space] = {sf::Keyboard::Key::Space, sf::Keyboard::Key::Space, 0, false, sf::Joystick::Axis::Z,  0.0f};
        _bindings[cmn::Keys::R]     = {sf::Keyboard::Key::R, sf::Keyboard::Key::R,    7, false, sf::Joystick::Axis::R,  0.0f};

        // Menu
        _bindings[cmn::Keys::MenuSolo]         = {sf::Keyboard::Key::Num1, sf::Keyboard::Key::Num1, 0, false, sf::Joystick::Axis::Z, 0.f};
        _bindings[cmn::Keys::MenuMatchmaking] = {sf::Keyboard::Key::Num2, sf::Keyboard::Key::Num2, 1, false, sf::Joystick::Axis::Z, 0.f};
        _bindings[cmn::Keys::MenuLobby]        = {sf::Keyboard::Key::Num3, sf::Keyboard::Key::Num3, 2, false, sf::Joystick::Axis::Z, 0.f};
        _bindings[cmn::Keys::MenuJoinLobby]        = {sf::Keyboard::Key::Num4, sf::Keyboard::Key::Num4, 2, false, sf::Joystick::Axis::Z, 0.f};
        _bindings[cmn::Keys::MenuLeave]        = {sf::Keyboard::Key::Escape, sf::Keyboard::Key::Escape, 3, false, sf::Joystick::Axis::Z, 0.f};
    }

    bool InputManager::isActionTriggered(cmn::Keys action) const
    {
        if (!_bindings.contains(action)) {
            return false;
        }
        const auto& bind = _bindings.at(action);
        if (bind.key != sf::Keyboard::Key::Unknown && (sf::Keyboard::isKeyPressed(bind.key) || sf::Keyboard::isKeyPressed(bind.other_key))) {
            return true;
        }
        if (sf::Joystick::isConnected(0)) {
            return _checkGamepad(bind);
        }
        return false;
    }

    bool InputManager::_checkGamepad(const InputBinding& bind) const
    {
        if (bind.isAxis) {
            float pos = sf::Joystick::getAxisPosition(0, bind.axis);
            return (bind.axisThreshold > 0) ? (pos > bind.axisThreshold) : (pos < bind.axisThreshold);
        } else {
            return sf::Joystick::isButtonPressed(0, bind.joystickButton);
        }
    }

    std::string InputManager::getShaderName() const
    {
        return _shader;
    }
}// namespace client