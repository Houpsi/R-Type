/*
** EPITECH PROJECT, 2025
** R_Type
** File description:
** EnemyFactory
*/

#ifndef R_TYPE_ENEMYFACTORY_HPP
#define R_TYPE_ENEMYFACTORY_HPP
#include "EntityFactory.hpp"


class EnemyFactory : public EntityFactory
{
    public:
    EnemyFactory() = default;
    ~EnemyFactory() override = default;
    EntityProduct* createEntity() override;
};


#endif// R_TYPE_ENEMYFACTORY_HPP
