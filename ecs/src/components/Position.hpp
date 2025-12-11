/*
** EPITECH PROJECT, 2025
** r-type_client
** File description:
** Position
*/

#ifndef BOOTSTRAP_POSITION_HPP
    #define BOOTSTRAP_POSITION_HPP
#include "Component.hpp"

namespace ecs {
class Position : public Component
{
  public:
    explicit Position(float x, float y) : _x(x), _y(y) {}
    ~Position() override = default;
    float getX() const;
    float getY() const;
    void setX(float x);
    void setY(float y);
  private:
    float _x;
    float _y;
};
}

#endif //BOOTSTRAP_POSITION_HPP