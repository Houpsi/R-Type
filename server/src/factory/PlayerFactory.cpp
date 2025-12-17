/*
** EPITECH PROJECT, 2025
** R_Type
** File description:
** PlayerFactory
*/

#include "PlayerFactory.hpp"

EntityProduct* createEntity()
{
    return new Player();
}