//
// Created by aleks on 27/11/2025.
//

#ifndef BOOTSTRAP_POSITION_HPP
#define BOOTSTRAP_POSITION_HPP
#include "Component.hpp"


namespace ECS {
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