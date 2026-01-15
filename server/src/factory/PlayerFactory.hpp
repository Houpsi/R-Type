/*
** EPITECH PROJECT, 2025
** R_Type
** File description:
** PlayerFactory
*/


#ifndef R_TYPE_PLAYERFACTORY_HPP
#define R_TYPE_PLAYERFACTORY_HPP
#include "EntityFactory.hpp"
#include "Player.hpp"


class PlayerFactory : public EntityFactory
{
    public:
    EntityProduct* createEntity() override;
};


#endif// R_TYPE_PLAYERFACTORY_HPP
