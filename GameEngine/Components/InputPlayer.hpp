//
// Created by aleks on 27/11/2025.
//

#ifndef BOOTSTRAP_INPUTPLAYER_HPP
#define BOOTSTRAP_INPUTPLAYER_HPP
#include "Component.hpp"


class InputPlayer : public Component {
    public:
    explicit InputPlayer(bool a) {
        this->_down = a;
    };
    ~InputPlayer() override = default;
public:
    bool _up;
    bool _down;
    bool _left;
    bool _right;
};


#endif //BOOTSTRAP_INPUTPLAYER_HPP