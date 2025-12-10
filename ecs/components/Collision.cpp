/*
** EPITECH PROJECT, 2025
** r-type_client
** File description:
** Collision
*/

#include "Collision.hpp"

namespace ECS {

    /**
     * @brief Returns the collision type
     * @return The TypeCollision value representing the kind of collision
     */
    TypeCollision Collision::getTypeCollision() const
    {
        return _typeCollision;
    }

    /**
     * @brief Sets the collision type
     * @param typeCollision The new collision type
     */
    void Collision::setTypeCollision(TypeCollision typeCollision)
    {
        _typeCollision = typeCollision;
    }

    /**
     * @brief Checks whether this collider is a trigger
     * A trigger detects collisions without producing physical blocking
     * @return True if the collider is a trigger, false otherwise
     */
    bool Collision::getIsTrigger() const
    {
        return _isTrigger;
    }

    /**
     * @brief Defines whether this collider is a trigger
     * @param isTrigger True to make this collider a trigger
     */
    void Collision::setIsTrigger(bool isTrigger)
    {
        _isTrigger = isTrigger;
    }

    /**
     * @brief Gets the collider height
     * @return The height of the collider
     */
    float Collision::getHeight() const
    {
        return _height;
    }

    /**
     * @brief Sets the collider height
     * @param height New height of the collider
     */
    void Collision::setHeight(float height)
    {
        _height = height;
    }

    /**
     * @brief Gets the collider width
     * @return The width of the collider
     */
    float Collision::getWidth() const
    {
        return _width;
    }

    /**
     * @bried Sets the collider width
     * @param width New width of the collider
     */
    void Collision::setWidth(float width)
    {
        _width = width;
    }
}
