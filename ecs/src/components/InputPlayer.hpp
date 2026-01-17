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
    [[nodiscard]] bool getReady() const;
    [[nodiscard]] bool getOne() const;
    [[nodiscard]] bool getTwo() const;
    [[nodiscard]] bool getThree() const;
    [[nodiscard]] bool getFour() const;
    void setUp(bool up);
    void setDown(bool down);
    void setLeft(bool left);
    void setRight(bool right);
    void setSpacebar(bool spacebar);
    void setOne(bool one);
    void setTwo(bool two);
    void setThree(bool three);
    void setFour(bool four);
    void setR(bool r);
    void setEscape(bool escape);

  private:
    bool _up = false;
    bool _down = false;
    bool _left = false;
    bool _right = false;
    bool _spacebar = false;
    bool _r = false;
    bool _escape = false;
    bool _one = false;
    bool _two = false;
    bool _three = false;
    bool _four = false;
};
}

#endif //INPUTPLAYER_HPP