/*
** EPITECH PROJECT, 2025
** r-type_client
** File description:
** Entity
*/

#include "Entity.hpp"

namespace ecs {
    size_t Entity::getId() const
    {
        return _id;
    }
}// namespace ecs