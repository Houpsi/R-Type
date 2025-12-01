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
        [[nodiscard]] bool getUp() const;
        [[nodiscard]] bool getDown() const;
        [[nodiscard]] bool getLeft() const;
        [[nodiscard]] bool getRight() const;
        void setUp(bool up);
        void setDown(bool down);
        void setLeft(bool left);
        void setRight(bool right);
    private:
        bool _up = false;
        bool _down = false;
        bool _left = false;
        bool _right = false;
};


#endif //INPUTPLAYER_HPP