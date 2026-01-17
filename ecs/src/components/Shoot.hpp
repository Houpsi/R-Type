/*
** EPITECH PROJECT, 2025
** r-type_client
** File description:
** Shoot
*/

#ifndef R_TYPE_CLIENT_SHOOT_HPP
    #define R_TYPE_CLIENT_SHOOT_HPP
#include "Component.hpp"
#include <unordered_map>
#include <vector>

namespace ecs {
    /**
     * @class Shoot class with damage and cooldown
     */
    class Shoot : public Component {
    public:
        enum class ShootingType {
            Normal,
            Shotgun,
            Gatling,
        };

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

        void addActiveShootingType(ShootingType type, float duration);
        std::vector<ShootingType> getActiveShootingTypes() const;

    private:
        float _cooldown;
        int _damage;
        float _timeSinceLastShot = 0;
        float _shootTimer;
        std::unordered_map<ShootingType, float> _activeShootingTypes;
    };
}

#endif //R_TYPE_CLIENT_SHOOT_HPP
