/*
** EPITECH PROJECT, 2025
** R_Type
** File description:
** EnemyFactory
*/

#include "EnemyFactory.hpp"
#include "EnemyProduct.hpp"

EntityProduct *EnemyFactory::createEntity()
{
    return new EnemyProduct();
}