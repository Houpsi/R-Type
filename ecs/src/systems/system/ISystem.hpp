/*
** EPITECH PROJECT, 2025
** r-type_client
** File description:
** System
*/

#ifndef BOOTSTRAP_SYSTEM_HPP
    #define BOOTSTRAP_SYSTEM_HPP
#include "managers/EcsManager.hpp"

namespace ecs {

class ISystem {
  public:
    ISystem() = default;
    virtual ~ISystem() = default;
    
    virtual void update(ecs::EcsManager &ecs) = 0;
	virtual void pushEntity(ecs::Entity) = 0;

};
}

#endif //BOOTSTRAP_SYSTEM_HPP