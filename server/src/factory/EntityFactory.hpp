/*
** EPITECH PROJECT, 2025
** R_Type
** File description:
** EntityFactory
*/


#ifndef R_TYPE_ENTITYFACTORY_HPP
#define R_TYPE_ENTITYFACTORY_HPP
#include "EntityProduct.hpp"


class EntityFactory
{
    public:
    virtual EntityProduct* createEntity() = 0;
    virtual ~EntityFactory() = default;
};


#endif// R_TYPE_ENTITYFACTORY_HPP
