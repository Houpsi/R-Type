/*
** EPITECH PROJECT, 2025
** r-type_client
** File description:
** System
*/

#ifndef BOOTSTRAP_SYSTEM_HPP
    #define BOOTSTRAP_SYSTEM_HPP
#include <memory>
#include <vector>

namespace ecs {

class Entity;
class EcsManager;

class System {
  public:
    System() = default;
    virtual ~System() = default;
    
    virtual void update(EcsManager &ecs) = 0;
};
}

#endif //BOOTSTRAP_SYSTEM_HPP