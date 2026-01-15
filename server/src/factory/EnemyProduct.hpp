/*
** EPITECH PROJECT, 2025
** R_Type
** File description:
** EnemyProduct
*/


#ifndef R_TYPE_ENEMYPRODUCT_HPP
#define R_TYPE_ENEMYPRODUCT_HPP

#include "Entity.hpp"
#include "EntityProduct.hpp"

#include <memory>

class EnemyProduct : public EntityProduct
{
    public:
    EnemyProduct() = default;
    ~EnemyProduct() override = default;
    void createEntityProduct(std::shared_ptr<ecs::Entity> &entity) override;

};


#endif// R_TYPE_ENEMYPRODUCT_HPP
