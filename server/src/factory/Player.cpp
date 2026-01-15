/*
** EPITECH PROJECT, 2025
** R_Type
** File description:
** Player
*/


#include "Player.hpp"
#include "components/Collision.hpp"
#include "components/Enemy.hpp"
#include "components/Health.hpp"
#include "components/Position.hpp"

#include <Entity.hpp>

void Player::createEntityProduct(std::shared_ptr<ecs::Entity> &entity)
{
    entity->addComponent<ecs::Health>(100);
    entity->addComponent<ecs::Position>(200, WINDOW_Y / 2);
    entity->addComponent<ecs::Collision>(ecs::TypeCollision::PLAYER, SIZE_X_PLAYER, SIZE_Y_PLAYER);
    entity->addComponent<ecs::Shoot>(50, 0.5);
}