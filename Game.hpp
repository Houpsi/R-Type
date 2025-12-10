/*
** EPITECH PROJECT, 2025
** r-type_client
** File description:
** Game
*/

#ifndef BOOTSTRAP_GAME_HPP
    #define BOOTSTRAP_GAME_HPP
#include <random>
#include "ecs/src/EcsManager.hpp"
#include "components/Enemy.hpp"
#include "components/Health.hpp"
#include "components/Position.hpp"
#include "components/Sprite.hpp"
#include "components/Sound.hpp"
#include "systems/InputSystem.hpp"
#include "systems/MovementSystem.hpp"
#include "systems/RenderSystem.hpp"
#include "VelocitySystem.hpp"
#include "systems/ShootSystem.hpp"
#include "systems/CollisionSystem.hpp"
#include "VelocitySystem.hpp"
#include "Collision.hpp"

#define WINDOW_X 1920
#define WINDOW_Y 1080

class Game {
    public:
        Game() : _ecs(ecs::EcsManager()) {}
        ~Game() = default;
        void run();
    private:
        ecs::EcsManager _ecs;
};

#endif //BOOTSTRAP_GAME_HPP