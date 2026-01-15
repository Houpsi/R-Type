/*
** EPITECH PROJECT, 2025
** R_Type
** File description:
** Player
*/

#ifndef R_TYPE_PLAYER_HPP
#define R_TYPE_PLAYER_HPP
#include "Entity.hpp"
#include "EntityProduct.hpp"
#include <iostream>
#include <memory>

class Player : public EntityProduct
{
    public:
        Player() = default;
        ~Player() override = default;
        void createEntityProduct(std::shared_ptr<ecs::Entity> &entity) override;
};


#endif// R_TYPE_PLAYER_HPP
