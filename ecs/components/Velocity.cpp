/*
** EPITECH PROJECT, 2025
** r-type_client
** File description:
** Velocity
*/

#include "Velocity.hpp"

namespace ecs {
    float Velocity::getVelocity() const
    {
        return _velocity;
    }

    void Velocity::setVelocity(float velocity)
    {
        _velocity = velocity;
    }

    int Velocity::getDirection() const
    {
        return _direction;
    }

    void Velocity::setDirection(int direction)
    {
        _direction = direction;
    }
}
