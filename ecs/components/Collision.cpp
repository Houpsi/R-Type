/*
** EPITECH PROJECT, 2025
** r-type_client
** File description:
** Collision
*/

#include "Collision.hpp"

namespace ECS {
    TypeCollision Collision::getTypeCollision() const
    {
        return _typeCollision;
    }

    void Collision::setTypeCollision(TypeCollision typeCollision)
    {
        _typeCollision = typeCollision;
    }

    bool Collision::getIsTrigger() const
    {
        return _isTrigger;
    }

    void Collision::setIsTrigger(bool isTrigger)
    {
        _isTrigger = isTrigger;
    }

    float Collision::getHeight() const
    {
        return _height;
    }

    void Collision::setHeight(float height)
    {
        _height = height;
    }

    float Collision::getLength() const
    {
        return _length;
    }

    void Collision::setLength(float length)
    {
        _length = length;
    }
}
