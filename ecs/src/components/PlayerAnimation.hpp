/*
** EPITECH PROJECT, 2025
** R_Type
** File description:
** PlayerAnimation
*/

#ifndef R_TYPE_PLAYERANIMATION_HPP
#define R_TYPE_PLAYERANIMATION_HPP
#include "Component.hpp"

#include <cstddef>

namespace ecs {
    class PlayerAnimation : public Component
    {
        public:
        PlayerAnimation();
        ~PlayerAnimation() override = default;
        [[nodiscard]] std::size_t getId() const;
        void updateAnimation(float dt, const bool isDown, const bool isUp);
        [[nodiscard]] int getAnimFrame() const;
        private:
        std::size_t _id = 0;
        int _animFrame = 0;
        float _animTimer = 0.f;
        float _animSpeed = 0.1f;
    };

}


#endif// R_TYPE_PLAYERANIMATION_HPP
