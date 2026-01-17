/*
** EPITECH PROJECT, 2025
** r-type_client
** File description:
** Shoot
*/

#ifndef R_TYPE_CLIENT_SHOOT_HPP
    #define R_TYPE_CLIENT_SHOOT_HPP
#include "Component.hpp"

namespace ecs {
    /**
     * @class Shoot class with damage and cooldown
     */
    class Shoot : public Component {
    public:
        explicit Shoot(int damage, float cooldown, float shootTimer = 0.0f): _damage(damage), _cooldown(cooldown), _shootTimer(shootTimer) {};
        ~Shoot() override = default;

        [[nodiscard]] int getDamage() const;
        void setDamage(int damage);

        [[nodiscard]] float getCooldown() const;
        void setCooldown(float cooldown);

        [[nodiscard]] float getShootTimer() const;
        void setShootTimer(float cooldown);

        float getTimeSinceLastShot() const;
        void setTimeSinceLastShot(float t);


    private:
        float _cooldown;
        int _damage;
        float _timeSinceLastShot = 0;
        float _shootTimer;
    };
}

#endif //R_TYPE_CLIENT_SHOOT_HPP
