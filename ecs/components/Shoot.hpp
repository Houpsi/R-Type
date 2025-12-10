/*
** EPITECH PROJECT, 2025
** r-type_client
** File description:
** Shoot
*/

#ifndef R_TYPE_CLIENT_SHOOT_HPP
#define R_TYPE_CLIENT_SHOOT_HPP

#include "Component.hpp"

namespace ECS {
    class Shoot : public Component {
    public:
        explicit Shoot(int damage, int cooldown): _damage(damage), _cooldown(cooldown) {};
        ~Shoot() override = default;

        [[nodiscard]] int getDamage() const;
        void setDamage(int damage);

        [[nodiscard]] int getCooldown() const;
        void setCooldown(int cooldown);

        int getTimeSinceLastShot() const;
        void setTimeSinceLastShot(int t);


    private:
        int _cooldown;
        int _damage;
        int _timeSinceLastShot = 0;
    };
}


#endif //R_TYPE_CLIENT_SHOOT_HPP
