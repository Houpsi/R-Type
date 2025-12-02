/*
** EPITECH PROJECT, 2025
** r-type_client
** File description:
** Collision
*/

#include "Collision.hpp"

namespace ECS {
    TypeCollision Collision::GetTypeCollision() const
    {
        return _typeCollision;
    }

    void Collision::SetTypeCollision(ECS::TypeCollision typeCollision)
    {
        _typeCollision = typeCollision;
    }

    bool Collision::GetIsTrigger() const
    {
        return _isTrigger;
    }

    void Collision::SetIsTrigger(bool isTrigger)
    {
        _isTrigger = isTrigger;
    }

    float Collision::GetHeight() const
    {
        return _height;
    }

    void Collision::SetHeight(float height)
    {
        _height = height;
    }

    float Collision::GetLength() const
    {
        return _length;
    }

    void Collision::SetLength(float length)
    {
        _length = length;
    }
}
