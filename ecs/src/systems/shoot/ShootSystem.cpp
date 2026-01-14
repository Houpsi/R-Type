/*
** EPITECH PROJECT, 2025
** r-type_client
** File description:
** ShootSystem
*/

#include "ShootSystem.hpp"
#include "components/animation/Animation.hpp"

namespace ecs {
    /**
     * @brief Shoot a project
     * If the player touches the key space, a projectile is sent
     * @param ecs
    */
    void ShootSystem::update(EcsManager &ecs)
    {
        for (auto const &entity : _entities) {
            auto input = ecs.getComponent<InputPlayer>(entity);
            // if (!ecs.getComponentManager().getComponent<Shoot>(entity)) continue;
            // if (input) {
                auto shoot = ecs.getComponent<Shoot>(entity);
                shoot.setTimeSinceLastShot(shoot.getTimeSinceLastShot() + ecs.getDeltaTime());

                if (input.getSpacebar()) {
                    if (shoot.getTimeSinceLastShot() >= shoot.getCooldown()) {
                        auto projectile = ecs.createEntity();

                        shoot.setTimeSinceLastShot(0);

                        ecs.addComponentToEntity<Position>(
                            projectile, Position(ecs.getComponent<Position>(entity).getX() + ecs.getComponent<Collision>(entity).getHeight(), ecs.getComponent<Position>(entity).getY()));

                        ecs.addComponentToEntity<Velocity>(projectile, Velocity(400, 1));
                        ecs.addComponentToEntity<Shoot>(projectile, Shoot(ecs.getComponent<Shoot>(entity).getDamage(), ecs.getComponent<Shoot>(entity).getCooldown()));
                        sf::Vector2f scale(1.0f, 1.0f);
                        ecs.addComponentToEntity<Sprite>(projectile, Sprite(ecs.getResourceManager().getTexture("./assets/r-typesheet30a.gif"), scale));
                        ecs.addComponentToEntity<Animation>(projectile, Animation(std::pair<int, int>(32, 36), 0, 3));
                        ecs.addComponentToEntity<Collision>(projectile, Collision(PLAYER_PROJECTILE, 10, 10));

                        // projectile->addComponent<ecs::Position>(
                        // ecs.getComponentManager().getComponent<Position>(entity).getX() + ecs.getComponentManager().getComponent<Collision>(entity).getHeight(), ecs.getComponentManager().getComponent<Position>(entity).getY());
                        // projectile->addComponent<Velocity>(400, 1);
                        // projectile->addComponent<Shoot>(ecs.getComponentManager().getComponent<Shoot>(entity).getDamage(), ecs.getComponentManager().getComponent<Shoot>(entity).getCooldown());
                        // projectile->addComponent<Sprite>(ecs.getResourceManager()
                                                            // .getTexture("./assets/r-typesheet30a.gif"), scale);
                        // projectile->addComponent<Animation>(std::pair<int, int>(34, 34), 0, 3);
                        // projectile->addComponent<Collision>(PLAYER_PROJECTILE, 10, 10);
                        // projectile->addComponent<Animation>(std::pair<int, int>(32, 36), 0, 3);
                    }
                }
            // }
        }
    }

    void ShootSystem::configure(EcsManager &ecs)
    {
        _targetSignature.set(ecs.getComponentType<InputPlayer>());
        _targetSignature.set(ecs.getComponentType<Shoot>());
        _targetSignature.set(ecs.getComponentType<Position>());
        _targetSignature.set(ecs.getComponentType<Collision>());
    }
}