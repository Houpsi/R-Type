/*
** EPITECH PROJECT, 2025
** R_Type
** File description:
** InputPlayer
*/

#ifndef INPUTPLAYER_HPP
#define INPUTPLAYER_HPP
#include "Component.hpp"


class InputPlayer : public Component {
    public:
        InputPlayer() = default;
        ~InputPlayer() override = default;
    private:
        bool _up = false;
        bool _down = false;
        bool _left = false;
        bool _right = false;
};


#endif //INPUTPLAYER_HPP