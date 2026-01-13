/*
** EPITECH PROJECT, 2025
** r-type_client
** File description:
** System
*/

#ifndef BOOTSTRAP_SYSTEM_HPP
    #define BOOTSTRAP_SYSTEM_HPP
#include <bitset>
#include "src/Constants.hpp"
#include "managers/EcsManager.hpp"

namespace ecs {
	class EcsManager;
	using Entity = uint32_t;

class ISystem {
  public:
    ISystem() = default;
    virtual ~ISystem() = default;
    
    virtual void update(EcsManager &ecs) = 0;
	virtual void pushEntity(Entity) = 0;
	virtual std::bitset<cmn::NB_COMPONENTS> getSignature() = 0;

};
}

#endif //BOOTSTRAP_SYSTEM_HPP