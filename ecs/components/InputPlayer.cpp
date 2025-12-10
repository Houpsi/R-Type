/*
** EPITECH PROJECT, 2025
** R_Type
** File description:
** InputPlayer
*/

#include "InputPlayer.hpp"

namespace ecs {
bool InputPlayer::getDown() const
{
    return _down;
}

bool InputPlayer::getLeft() const
{
    return _left;
}

bool InputPlayer::getRight() const
{
    return _right;
}

bool InputPlayer::getUp() const
{
    return _up;
}

bool InputPlayer::getSpacebar() const
{
    return _spacebar;
}

void InputPlayer::setDown(bool down)
{
    _down = down;
}

void InputPlayer::setLeft(bool left)
{
    _left = left;
}

void InputPlayer::setRight(bool right)
{
    _right = right;
}

void InputPlayer::setUp(bool up)
{
    _up = up;
}

void InputPlayer::setSpacebar(bool spacebar)
{
    _spacebar = spacebar;
}

std::size_t InputPlayer::getId() const {
    return _id;
}

int InputPlayer::getAnimFrame() const
{
    return _animFrame;
}

void InputPlayer::updateAnimation(const float dt)
{
    if (getUp() || getDown()) {
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
