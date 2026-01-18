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
            explicit Velocity(float velocity, std::pair<float, float> direction): _velocity(velocity), _direction(direction) {};
            ~Velocity() override = default;

            float getVelocity() const;
            void setVelocity(float velocity);

            std::pair<float, float> getDirection() const;
            void setDirection(std::pair<float, float> direction);

        private:
            float _velocity;
            std::pair<float, float> _direction;
    };
}

#endif //R_TYPE_CLIENT_VELOCITY_HPP
