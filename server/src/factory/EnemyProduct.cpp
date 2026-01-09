/*
** EPITECH PROJECT, 2025
** R_Type
** File description:
** EnemyProduct
*/

#include "EnemyProduct.hpp"

#include "components/Collision.hpp"
#include "components/Enemy.hpp"
#include "components/Position.hpp"

#include <chrono>
#include <random>

void EnemyProduct::createEntityProduct(std::shared_ptr<ecs::Entity> &entity)
{
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::minstd_rand0 generator (seed);
    int const randNum = generator() % (WINDOW_Y + 1);

    entity->addComponent<ecs::Enemy>();
    entity->addComponent<ecs::Collision>(ecs::TypeCollision::ENEMY, 14, 18);
    entity->addComponent<ecs::Health>(100);
    entity->addComponent<ecs::Position>(WINDOW_X + 100, randNum);


}