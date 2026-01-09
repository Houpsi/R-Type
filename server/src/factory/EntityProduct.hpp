/*
** EPITECH PROJECT, 2025
** R_Type
** File description:
** Entity
*/

#ifndef R_TYPE_ENTITY_HPP
#define R_TYPE_ENTITY_HPP
#include <Entity.hpp>

constexpr int  SIZE_X_PLAYER = 33;
constexpr int SIZE_Y_PLAYER = 17;
constexpr int  WINDOW_X =  1920;
constexpr int  WINDOW_Y = 1080;

class EntityProduct
{
    public:
        virtual void createEntityProduct(std::shared_ptr<ecs::Entity> &entity) = 0;
        virtual ~EntityProduct() = default;
};


#endif// R_TYPE_ENTITY_HPP
