/*
** EPITECH PROJECT, 2025
** r-type_client
** File description:
** Game
*/

#ifndef BOOTSTRAP_GAME_HPP
#define BOOTSTRAP_GAME_HPP
#include "EcsManager.hpp"
#include <random>

#define WINDOW_X 1920
#define WINDOW_Y 1080

class Game {
    public:
        Game() : _ecs(ECS::EcsManager()) {}
        ~Game() = default;
        void run();
    private:
        ECS::EcsManager _ecs;

};


#endif //BOOTSTRAP_GAME_HPP