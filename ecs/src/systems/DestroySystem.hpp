/*
** EPITECH PROJECT, 2025
** r-type_client
** File description:
** DestroySystem
*/

#ifndef R_TYPE_CLIENT_DESTROYSYSTEM_HPP
#define R_TYPE_CLIENT_DESTROYSYSTEM_HPP

#define DESTROY_THRESHOLD (-50)

#include "EcsManager.hpp"

namespace ECS {
class DestroySystem : public System
{
  public:
    DestroySystem() = default;
    void update(EcsManager &ecs) override;
};
}


#endif// R_TYPE_CLIENT_DESTROYSYSTEM_HPP
