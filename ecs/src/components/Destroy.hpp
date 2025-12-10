/*
** EPITECH PROJECT, 2025
** r-type_client
** File description:
** Destroy
*/

#ifndef R_TYPE_CLIENT_DESTROY_HPP
#define R_TYPE_CLIENT_DESTROY_HPP

#include "Component.hpp"

namespace ECS {
class Destroy : public Component
{
  public:
    Destroy() = default;
    ~Destroy() override = default;
};
}


#endif// R_TYPE_CLIENT_DESTROY_HPP
