/*
** EPITECH PROJECT, 2025
** R_Type
** File description:
** EntityManager
*/

#ifndef R_TYPE_ENTITYMANAGER_HPP
#define R_TYPE_ENTITYMANAGER_HPP

#include <cstdint>
#include <queue>
#include <array>
#include <bitset>
#include "src/Constants.hpp"

namespace ecs {

    using Entity = uint32_t;
    using Signature = std::bitset<cmn::NB_COMPONENTS>;

    class EntityManager {
    public:
        Entity createEntity();
        void deleteEntity(Entity id);
        void setSignature(Entity entity, Signature newSignature);
        Signature getSignature(Entity entity);

    private:
        std::queue<Entity> _availableEntities;
        std::array<Signature, cmn::MAX_ENTITIES> _signatures;
        uint64_t _livingEntityCount = 0;
    };
}


#endif //R_TYPE_ENTITYMANAGER_HPP
