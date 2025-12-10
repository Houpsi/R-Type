/*
** EPITECH PROJECT, 2025
** r-type_client
** File description:
** Velocity
*/

#ifndef R_TYPE_CLIENT_VELOCITY_HPP
    #define R_TYPE_CLIENT_VELOCITY_HPP
#include "Component.hpp"

namespace ecs {
/**
 * @class Velocity class in function of the speed and the direction
 */
class Velocity : public Component {
    public:
        explicit Velocity(float velocity, int direction): _velocity(velocity), _direction(direction) {};
        ~Velocity() override = default;

        float getVelocity() const;
        void setVelocity(float velocity);

        int getDirection() const;
        void setDirection(int direction);

    private:
        float _velocity;
        int _direction;
};
}

#endif //R_TYPE_CLIENT_VELOCITY_HPP
