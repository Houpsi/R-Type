/*
** EPITECH PROJECT, 2025
** r-type_client
** File description:
** Shoot
*/

#include "Shoot.hpp"
#include "EcsConstant.hpp"
#include <random>

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

    /**
     * @brief Gets the shooter time
     * @return The shoot timer
     */
    float Shoot::getShootTimer() const
    {
        return _shootTimer;
    }

    /**
     * @brief Sets the shooter
     * @param t New shot of the shoot
     */
    void Shoot::setShootTimer(float t)
    {
        _shootTimer = t;
    }

    void Shoot::setActiveShootingType(ShootingType type)
    {
        _activeShootingType.first = type;
        if (type == ShootingType::Shotgun) {
            _activeShootingType.second = nbAmmoShotgun;
        }
        if (type == ShootingType::Gatling) {
            _activeShootingType.second = nbAmmoGatling;
        }
    }

    Shoot::ShootingType Shoot::getActiveShootingType() const
    {
        return _activeShootingType.first;
    }

    void Shoot::updateShootingType()
    {
        if (_activeShootingType.second == 0) {
            _activeShootingType.first = Shoot::ShootingType::Normal;
            _activeShootingType.second = nbAmmoNormalGun;
        } else {
            _activeShootingType.second -= 1;
        }
    }

    Shoot::ShootingType Shoot::getRandomShootingType()
    {
        static std::random_device rand;
        static std::mt19937 gen(rand());

        std::uniform_int_distribution<> distrib(1, 2);
        return static_cast<ShootingType>(distrib(gen));
    }


}
