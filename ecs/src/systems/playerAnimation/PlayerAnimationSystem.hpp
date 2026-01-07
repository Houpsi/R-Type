/*
** EPITECH PROJECT, 2025
** r-type_client
** File description:
** PlayerAnimationSystem
*/

#ifndef R_TYPE_CLIENT_PLAYERANIMATIONSYSTEM_HPP
#define R_TYPE_CLIENT_PLAYERANIMATIONSYSTEM_HPP
#include "../system/System.hpp"
#include "components/animation/Animation.hpp"
#include "managers/EcsManager.hpp"
#include "components/inputPlayer/InputPlayer.hpp"
#include "components/sprite/Sprite.hpp"

namespace ecs {
class PlayerAnimationSystem : public System
{
    public:
        PlayerAnimationSystem() = default;
        ~PlayerAnimationSystem() override = default;
        void update(EcsManager &ecs) override;

};
}



#endif// R_TYPE_CLIENT_PLAYERANIMATIONSYSTEM_HPP
