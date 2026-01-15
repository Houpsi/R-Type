/*
** EPITECH PROJECT, 2025
** R_Type
** File description:
** Game
*/

#ifndef R_TYPE_GAME_HPP
#define R_TYPE_GAME_HPP

#include "EcsManager.hpp"
#include "SFML/Graphics/Font.hpp"
#include "SFML/Graphics/Text.hpp"
#include "SFML/Graphics/RenderWindow.hpp"
#include "data_translator/DataTranslator.hpp"
#include "shared_data/SharedData.hpp"

namespace client {
    class GameRenderer {
    public:
        explicit GameRenderer(const std::shared_ptr<cmn::SharedData>&);
        void run();
    private:
        ecs::EcsManager _ecs;
        std::shared_ptr<cmn::SharedData> _sharedData;
        sf::RenderWindow _window;
        sf::Clock _clock;
        sf::Clock enemyClock;
        cmn::DataTranslator _translator{};
        std::shared_ptr<ecs::Entity> _keyboard;
        std::shared_ptr<ecs::Entity> _sound;

        void _handleEvents();
        void _initEcsSystem();
        void _initBackground();
        void _initKeyboard();
        void _checkPlayerInput();
        void _updateNetwork();
        void _updateLobby();
        void _updateGame();
        void _initSound();


        bool _isRunning = false;
        uint32_t _playerId = 0;

    };
}


#endif //R_TYPE_GAME_HPP
