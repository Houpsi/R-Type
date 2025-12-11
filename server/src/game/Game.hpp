/*
** EPITECH PROJECT, 2025
** R_Type
** File description:
** Game
*/

#ifndef R_TYPE_GAME_HPP
#define R_TYPE_GAME_HPP
#define WINDOW_X 1920
#define WINDOW_Y 1080
#include "EcsManager.hpp"
#include "SFML/Graphics/RenderWindow.hpp"

namespace server {
    class Game {
    public:
        Game() : _ecs(ecs::EcsManager()) {}
        ~Game() = default;
        void run();
    private:
        ecs::EcsManager _ecs;
    };
}

#endif //R_TYPE_GAME_HPP
