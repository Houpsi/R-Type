/*
** EPITECH PROJECT, 2025
** R_Type
** File description:
** InputPlayer
*/

#ifndef INPUTPLAYER_HPP
    #define INPUTPLAYER_HPP
#include "Component.hpp"
#include <cstddef>

namespace ecs {
class InputPlayer : public Component {
  public:
    InputPlayer() = default;
    ~InputPlayer() override = default;
    [[nodiscard]] bool getUp() const;
    [[nodiscard]] bool getDown() const;
    [[nodiscard]] bool getLeft() const;
    [[nodiscard]] bool getRight() const;
    [[nodiscard]] bool getSpacebar() const;
    void setUp(bool up);
    void setDown(bool down);
    void setLeft(bool left);
    void setRight(bool right);
    void setSpacebar(bool spacebar);
  private:
    bool _up = false;
    bool _down = false;
    bool _left = false;
    bool _right = false;
    bool _spacebar = false;

};
}

#endif //INPUTPLAYER_HPP