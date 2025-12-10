/*
** EPITECH PROJECT, 2025
** r-type_client
** File description:
** SpriteAnimationSystem
*/


#ifndef R_TYPE_CLIENT_SPRITEANIMATIONSYSTEM_HPP
#define R_TYPE_CLIENT_SPRITEANIMATIONSYSTEM_HPP
#include "System.hpp"

namespace ecs {

class SpriteAnimationSystem : public System
{
    public:
        SpriteAnimationSystem() = default;
        ~SpriteAnimationSystem() override = default;
        void update(EcsManager &ecs) override;
};
}



#endif// R_TYPE_CLIENT_SPRITEANIMATIONSYSTEM_HPP
