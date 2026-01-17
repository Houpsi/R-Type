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
#include "SFML/Graphics/RenderWindow.hpp"
#include "client_shared_data/ClientSharedData.hpp"
#include "data_translator/DataTranslator.hpp"
#include "input_manager/InputManager.hpp"

namespace client {

    enum class ClientState {
        Menu,
        Waiting,
        InGame,
        GameOver,
        EnteringLobbyCode
    };

    class GameRenderer {
    public:
        explicit GameRenderer(const std::shared_ptr<ClientSharedData>&);
        void run();
    private:
        ecs::EcsManager _gameEcs;
        ecs::EcsManager _menuEcs;
        std::shared_ptr<ClientSharedData> _sharedData;
        sf::RenderWindow _window;
        sf::Clock _clock;
        sf::Clock enemyClock;
        cmn::DataTranslator _translator{};
        std::shared_ptr<ecs::Entity> _sound;
        InputManager _inputManager;
        std::shared_ptr<ecs::Entity> _gameKeyboard;
        std::shared_ptr<ecs::Entity> _menuKeyboard;
        ClientState _currentState = ClientState::Menu;
        uint32_t _playerId = 0;
        std::map<cmn::Keys, bool> _previousInputs;
        std::map<cmn::Keys, bool> _previousMenuInputs;

        std::string _lobbyCodeInput;
        static constexpr size_t MAX_CODE_LENGTH = 6;

        void _handleEvents();
        void _initEcsSystem();
        void _initBackground();
        void _initKeyboard();
        void _checkGamePlayerInput();
        void _checkMenuPlayerInput();
        void _updateNetwork();
        void _initSound();
        void _initScore();
        void _updateMenu(sf::Clock &inputClock, float elapsedTime, float deltaTime);
        void _updateGame(sf::Clock &inputClock, float elapsedTime, float deltaTime);
        void _resetGame();
        void _clearGameEntities();
        void _handleCodeInput(const sf::Event::KeyPressed& keyEvent);

    };
}


#endif //R_TYPE_GAME_HPP
