/*
** EPITECH PROJECT, 2025
** r-type_client
** File description:
** Shoot
*/

#include "Shoot.hpp"

namespace ecs {
    /**
     * @brief Gets the shoot damage
     * @return The damage of the shoot
     */
    int Shoot::getDamage() const
    {
        return _damage;
    }

    /**
     * @brief Sets the shoot damage
     * @param damage New damage of the shoot
     */
    void Shoot::setDamage(int damage)
    {
        _damage = damage;
    }

    /**
     * @brief Gets the shoot cooldown
     * @return The cooldown of the shoot
     */
    float Shoot::getCooldown() const
    {
        return _cooldown;
    }

    /**
     * @brief Sets the shoot cooldown
     * @param cooldown New cooldown of the shoot
     */
    void Shoot::setCooldown(float cooldown)
    {
        _cooldown = cooldown;
    }

    /**
     * @brief Gets the last shot
     * @return The last shot
     */
    float Shoot::getTimeSinceLastShot() const
    {
        return _timeSinceLastShot;
    }

    /**
     * @brief Sets the last shot
     * @param t New shot of the shoot
     */
    void Shoot::setTimeSinceLastShot(float t)
    {
        _timeSinceLastShot = t;
    }
}
