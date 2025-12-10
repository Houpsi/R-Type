/*
** EPITECH PROJECT, 2025
** r-type_client
** File description:
** ShootSystem
*/

#include "ShootSystem.hpp"

namespace ecs {
/**
 * @brief Shoot a project
 * If the player touch the key space a projectile is send
 * @param ecs
 */
void ShootSystem::update(EcsManager &ecs)
{
    for (auto const &entity : ecs.getEntitiesWithComponent<InputPlayer>()) {
        auto input = entity->getComponent<InputPlayer>();
        if (!entity->getComponent<Shoot>()) continue;
        if (input) {
            entity->getComponent<Shoot>()->setTimeSinceLastShot(
                entity->getComponent<Shoot>()->getTimeSinceLastShot() + ecs.deltaTime());

            auto shoot= entity->getComponent<Shoot>();
            if (input->getSpacebar()) {
                if (shoot->getTimeSinceLastShot() >= shoot->getCooldown()) {
                    auto projectile = ecs.createEntity();

                    shoot->setTimeSinceLastShot(0);
                    projectile->addComponent<ecs::Position>(entity->getComponent<Position>()->getX(), entity->getComponent<Position>()->getY());
                    projectile->addComponent<Velocity>(400, 1);
                    projectile->addComponent<Sprite>("./assets/r-typesheet30a.gif");
                    projectile->addComponent<Collision>(ecs::TypeCollision::PLAYER_PROJECTILE, 10, 10);
                }
            }
        }
    }
}
}
