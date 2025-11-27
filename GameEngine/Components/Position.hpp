//
// Created by aleks on 27/11/2025.
//

#ifndef BOOTSTRAP_POSITION_HPP
#define BOOTSTRAP_POSITION_HPP
#include "Component.hpp"


class Position : public Component {
    private:
        float x;
        float y;
    public:
        explicit Position(int x, int y) {
            this->x = x;
            this->y = y;
        };
        ~Position() = default;
        float getX() const {
            return x;
        };
        float getY() const {
            return y;
        };
        void setX(const float x) {
            this->x = x;
        };
        void setY(const float y) {
            this->y = y;
        };
};


#endif //BOOTSTRAP_POSITION_HPP