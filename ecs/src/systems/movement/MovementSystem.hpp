/*
** EPITECH PROJECT, 2025
** R_Type
** File description:
** MovementSystem
*/


#ifndef MOVEMENTSYSTEM_HPP
    #define MOVEMENTSYSTEM_HPP
#include "systems/system/ASystem.hpp"
#include "managers/EcsManager.hpp"
#include "components/position/Position.hpp"
#include "components/enemy/Enemy.hpp"
#include "components/inputPlayer/InputPlayer.hpp"
#include "components/collision/Collision.hpp"
#include "components/destroy/Destroy.hpp"

namespace ecs {
    class MovementSystem : public ASystem
    {
    public:
        ~MovementSystem() override = default;
        void update(EcsManager &ecs) override;
        void configure(EcsManager &ecs) override;
    };
}


#endif //MOVEMENTSYSTEM_HPP