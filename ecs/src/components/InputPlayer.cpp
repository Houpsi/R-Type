/*
** EPITECH PROJECT, 2025
** R_Type
** File description:
** InputPlayer
*/

#include "InputPlayer.hpp"
#include <iostream>

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

    bool InputPlayer::getReady() const
    {
        return _r;
    }

    bool InputPlayer::getOne() const
    {
        return _one;
    }

    bool InputPlayer::getTwo() const
    {
        return _two;
    }

    bool InputPlayer::getThree() const
    {
        return _three;
    }

    bool InputPlayer::getFour() const
    {
        return _four;
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
    void InputPlayer::setR(bool r)
    {
        _r = r;
    }

    void InputPlayer::setEscape(bool escape)
    {
        _escape = escape;
    }

    void InputPlayer::setOne(bool one)
    {
        _one = one;
    }

    void InputPlayer::setTwo(bool two)
    {
        _two = two;
    }

    void InputPlayer::setThree(bool three)
    {
        _three = three;
    }

    void InputPlayer::setFour(bool four)
    {
        _four = four;
    }

}
