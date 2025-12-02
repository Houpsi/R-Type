/*
** EPITECH PROJECT, 2025
** r-type_client
** File description:
** Health
*/

#ifndef BOOTSTRAP_HEALTH_HPP
#define BOOTSTRAP_HEALTH_HPP
#include "Component.hpp"


namespace ECS {
class Health : public Component {
  private:
    int _health = 0;
  public:
    Health(int const health) : _health(health) {};
    ~Health() = default;
    int getHealth() const;
    void setHealth(int const health);
};
}


#endif //BOOTSTRAP_HEALTH_HPP