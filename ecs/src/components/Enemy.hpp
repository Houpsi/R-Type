/*
** EPITECH PROJECT, 2025
** r-type_client
** File description:
** Enemy
*/

#ifndef R_TYPE_ENEMY_HPP
    #define R_TYPE_ENEMY_HPP
#include "Component.hpp"

namespace ecs {
class Enemy : public Component
{
  public:
    explicit Enemy() = default;
    ~Enemy() override = default;

  private:
    int _id;
    int _type;
};
}

#endif //R_TYPE_ENEMY_HPP
