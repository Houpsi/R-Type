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
#include "../../common/src/Constants.hpp"

namespace ecs {

    using Entity = uint32_t;

    class EntityManager {
    public:
        Entity createEntity();
        void deleteEntity(Entity id);
    private:
        std::queue<Entity> _availableEntities;
        std::array<std::bitset<cmn::NB_COMPONENTS>, cmn::MAX_ENTITIES> _signatures;
        uint64_t _livingEntityCount = 0;
    };
}


#endif //R_TYPE_ENTITYMANAGER_HPP
