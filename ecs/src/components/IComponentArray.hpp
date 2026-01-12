/*
** EPITECH PROJECT, 2026
** R_Type
** File description:
** IComponentArray
*/

#ifndef R_TYPE_ICOMPONENTARRAY_HPP
#define R_TYPE_ICOMPONENTARRAY_HPP

#include "managers/EntityManager.hpp"

namespace ecs {
    class IComponentArray {
    public:
        virtual ~IComponentArray() = default;
        virtual void entityDestroyed(Entity entity) = 0;
    };
}

#endif //R_TYPE_ICOMPONENTARRAY_HPP
