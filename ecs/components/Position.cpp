/*
** EPITECH PROJECT, 2025
** R_Type
** File description:
** Position
*/


#include "Position.hpp"

namespace ECS {
float Position::getX() const {
    return _x;
}

float Position::getY() const {
    return _y;
};

void Position::setX(const float x) {
    this->_x = x;
};

void Position::setY(const float y) {
    this->_y = y;
};
}