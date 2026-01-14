/*
** EPITECH PROJECT, 2025
** r-type_client
** File description:
** System
*/

#ifndef BOOTSTRAP_SYSTEM_HPP
    #define BOOTSTRAP_SYSTEM_HPP
#include <bitset>
#include "src/constants/GameConstants.hpp"
#include "managers/EntityManager.hpp"

namespace ecs {
	class EcsManager;

    class ISystem {
    public:
        ISystem() = default;
        virtual ~ISystem() = default;

        virtual void update(EcsManager &ecs) = 0;
        virtual void configure(EcsManager &ecs) = 0;
        virtual Signature getSignature() = 0;
        virtual void addEntity(ecs::Entity entity) = 0;
        virtual void removeEntity(ecs::Entity entity) = 0;

};
}

#endif //BOOTSTRAP_SYSTEM_HPP