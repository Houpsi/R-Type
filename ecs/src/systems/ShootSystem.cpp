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
     * If the player touches the key space, a projectile is sent
     * @param ecs
     */
    void ShootSystem::update(EcsManager &ecs)
    {
        for (auto const &entity : ecs.getEntitiesWithComponent<InputPlayer>()) {
            auto input = entity->getComponent<InputPlayer>();
            if (!entity->getComponent<Shoot>()) continue;
            if (input) {
                const auto shoot = entity->getComponent<Shoot>();
                shoot->setTimeSinceLastShot(shoot->getTimeSinceLastShot() + ecs.getDeltaTime());

                if (input->getSpacebar()) {
                    if (shoot->getTimeSinceLastShot() >= shoot->getCooldown()) {
                        auto projectile = ecs.createEntity();

                        shoot->setTimeSinceLastShot(0);
                        projectile->addComponent<ecs::Position>(
                            entity->getComponent<Position>()->getX() + entity->getComponent<Collision>()->getHeight(), entity->getComponent<Position>()->getY());
                        projectile->addComponent<Velocity>(400, 1);
                        projectile->addComponent<Shoot>(
                            entity->getComponent<Shoot>()->getDamage(), entity->getComponent<Shoot>()->getCooldown());
                        sf::Vector2f scale(1.0f, 1.0f);
                        projectile->addComponent<Sprite>("./assets/r-typesheet30a.gif", scale);
                        projectile->addComponent<Animation>(std::pair<int, int>(34, 34), 0, 3);
                        projectile->addComponent<Collision>(ecs::TypeCollision::PLAYER_PROJECTILE, 10, 10);
                    }
                }
            }
        }
    }
}