/*
** EPITECH PROJECT, 2025
** r-type_client
** File description:
** Health
*/

#include "Health.hpp"
#include <stdexcept>

namespace ecs {
    Health::Health(const int health) : _health(health)
    {
        if (health < 0) {
            throw std::invalid_argument("Health cannot be negative");
        }
    }

    /**
     * @breif Gets the health
     * @return the health of the component
     */
    int Health::getHealth() const
    {
        return _health;
    }

    /**
     * @brief Sets the health
     * @param health New health of the component
     */
    void Health::setHealth(const int health)
    {
        _health = health;
    }
}