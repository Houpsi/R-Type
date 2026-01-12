/*
** EPITECH PROJECT, 2025
** r-type_client
** File description:
** Animation
*/

#include "Animation.hpp"


namespace ecs {

void Animation::updateAnimation(const float dt)
{
    if (_numberFrame <= 1)
        return;
    _animTimer += dt;
    if (_animTimer >= _animSpeed) {
        _animTimer = 0.f;
        _animFrame = (_animFrame + 1) % _numberFrame;
    }
}

int Animation::getAnimFrame() const
{
    return _animFrame;
}

int Animation::getNumberFrame() const
{
    return _numberFrame;
}
float Animation::getAnimTimer() const
{
    return _animTimer;
}
void Animation::setAnimTimer(const float animTimer)
{
    _animTimer = animTimer;
};
void Animation::setAnimFrame(const int animFrame)
{
    _animFrame = animFrame;
};
float Animation::getAnimSpeed() const
{
    return _animSpeed;
};
int Animation::getOffsetX() const
{
    return _offsetX;
};
std::pair<int,int> Animation::getSpriteSize()
{
    return _sizeSprite;
};
}// namespace ECS