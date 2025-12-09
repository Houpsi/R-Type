/*
** EPITECH PROJECT, 2025
** r-type_client
** File description:
** ShootSystem
*/

#include "ShootSystem.hpp"

namespace ECS {
/**
 * @brief Shoot a project
 * If the player touch the key space a projectile is send
 * @param ecs
 */
void ShootSystem::update(EcsManager &ecs)
{
    for (auto const &entity : ecs.getEntitiesWithComponent<InputPlayer>()) {
        auto input = entity->getComponent<InputPlayer>();
        if (input) {
            if (input->getSpacebar()) {
                entity->getComponent<Shoot>()->setTimeSinceLastShot(0);
                auto projectile = ecs.createEntity();

                projectile->addComponent<ECS::Position>(entity->getComponent<Position>()->getX(), entity->getComponent<Position>()->getY());
//                projectile->addComponent<Velocity>(0, -10); TO DO when velocity is done
                projectile->addComponent<Shoot>(entity->getComponent<Shoot>()->getDamage(), entity->getComponent<Shoot>()->getCooldown());
                projectile->addComponent<Sprite>("./assets/r-typesheet30a.gif");
                projectile->addComponent<Collision>(ECS::TypeCollision::PLAYER_PROJECTILE, 10, 10);
            }
        }
    }

}
}
