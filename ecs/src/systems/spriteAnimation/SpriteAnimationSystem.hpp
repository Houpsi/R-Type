/*
** EPITECH PROJECT, 2025
** r-type_client
** File description:
** SpriteAnimationSystem
*/


#ifndef R_TYPE_CLIENT_SPRITEANIMATIONSYSTEM_HPP
#define R_TYPE_CLIENT_SPRITEANIMATIONSYSTEM_HPP
#include "systems/system/ASystem.hpp"

namespace ecs {
    class SpriteAnimationSystem : public ASystem
    {
    public:
        explicit SpriteAnimationSystem() {};
        ~SpriteAnimationSystem() override = default;
        void update(EcsManager &ecs) override;
        void configure(EcsManager &ecs) override;
    };
}



#endif// R_TYPE_CLIENT_SPRITEANIMATIONSYSTEM_HPP
