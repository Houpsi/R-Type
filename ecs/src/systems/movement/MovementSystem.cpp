/*
** EPITECH PROJECT, 2025
** R_Type
** File description:
** MovementSystem
*/

#include "MovementSystem.hpp"

namespace ecs {
    void MovementSystem::update(EcsManager &ecs)
    {
        const float dt = ecs.getDeltaTime();
        for (auto const &entity : _entities) {
            auto pos = ecs.getComponent<Position>(entity);
            auto input = ecs.getComponent<InputPlayer>(entity);

            // if (input) {
            if (input.getUp()) {
                pos.setY(pos.getY() - (cmn::playerSpeed * dt));
            }
            if (input.getDown()) {
                pos.setY(pos.getY() + (cmn::playerSpeed * dt));
            }
            if (input.getLeft()) {
                pos.setX(pos.getX() - (cmn::playerSpeed * dt));
            }
            if (input.getRight()) {
                pos.setX(pos.getX() + (cmn::playerSpeed * dt));
            }
            // }
        }
    // for (auto const &enemy : ecs.getEntitiesWithComponent<Enemy>()) {
    //     auto pos = enemy->getComponent<Position>();
    //     if (pos) {
    //         pos->setX(pos->getX() + (-playerSpeed * dt));
    //     }
    //     if (pos->getX() < 0 - enemy->getComponent<Collision>()->getWidth()) {
    //         enemy->addComponent<Destroy>();
    //     }
    //     if (pos->getX() > windowWidth + enemy->getComponent<Collision>()->getWidth() + 500) {
    //         enemy->addComponent<Destroy>();
    //     }
    // }
    }

    void MovementSystem::configure(EcsManager &ecs)
    {
        _targetSignature.set(ecs.getComponentType<InputPlayer>());
        _targetSignature.set(ecs.getComponentType<Position>());
    }
}
