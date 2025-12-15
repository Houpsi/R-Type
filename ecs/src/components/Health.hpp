/*
** EPITECH PROJECT, 2025
** r-type_client
** File description:
** Health
*/

#ifndef BOOTSTRAP_HEALTH_HPP
#define BOOTSTRAP_HEALTH_HPP
#include "Component.hpp"

namespace ecs {
    class Health : public Component {
      public:
        explicit Health(int const health);
        ~Health() override = default;
        [[nodiscard]] int getHealth() const;
        void setHealth(int const health);

      private:
        int _health = 0;
    };
}

#endif //BOOTSTRAP_HEALTH_HPP