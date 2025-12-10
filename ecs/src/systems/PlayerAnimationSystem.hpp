/*
** EPITECH PROJECT, 2025
** r-type_client
** File description:
** PlayerAnimationSystem
*/

#ifndef R_TYPE_CLIENT_PLAYERANIMATIONSYSTEM_HPP
#define R_TYPE_CLIENT_PLAYERANIMATIONSYSTEM_HPP
#include "System.hpp"
#include "Animation.hpp"
#include "EcsManager.hpp"
#include "InputPlayer.hpp"
#include "Sprite.hpp"

namespace ECS {
class PlayerAnimationSystem : public System
{
    public:
        PlayerAnimationSystem() = default;
        ~PlayerAnimationSystem() override = default;
        void update(EcsManager &ecs) override;

};
}



#endif// R_TYPE_CLIENT_PLAYERANIMATIONSYSTEM_HPP
