/*
** EPITECH PROJECT, 2025
** R_Type
** File description:
** PlayerAnimation
*/


#include "PlayerAnimation.hpp"

namespace ecs {
    std::size_t PlayerAnimation::getId() const
    {
        return _id;
    }

    int PlayerAnimation::getAnimFrame() const
    {
        return _animFrame;
    }

    void PlayerAnimation::updateAnimation(const float dt, const bool isDown, const bool isUp)
    {
        if (isDown || isUp) {
            _animTimer += dt;
            if (_animTimer >= _animSpeed) {
                _animTimer = 0.f;
                _animFrame++;
                if (_animFrame > 2)
                    _animFrame = 2;
            }
        } else {
            _animFrame = 0;
            _animTimer = 0.f;
        }
    }
}