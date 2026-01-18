/*
** EPITECH PROJECT, 2025
** r-type_client
** File description:
** Velocity
*/

#include <utility>
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

    std::pair<float, float> Velocity::getDirection() const
    {
        return _direction;
    }

    void Velocity::setDirection(std::pair <float, float> direction)
    {
        _direction = direction;
    }
}
