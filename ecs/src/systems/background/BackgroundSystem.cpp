/*
** EPITECH PROJECT, 2025
** R_Type
** File description:
** BackgroundSystem
*/

#include "BackgroundSystem.hpp"
#include "components/position/Position.hpp"
#include "managers/EcsManager.hpp"
#include "components/background/Background.hpp"

namespace ecs {

    void BackgroundSystem::configure(ecs::EcsManager &ecs)
    {
        _targetSignature.set(ecs.getComponentType<Background>());
        _targetSignature.set(ecs.getComponentType<Position>());
    }

    void BackgroundSystem::update(EcsManager &ecs)
    {
        for (const auto& entity : _entities) {
            if (!ecs.entityHasComponent<Position, Background>(entity)) {
                continue;
            }
            auto pos = ecs.getComponent<Position>(entity);
            auto parallax = ecs.getComponent<Background>(entity);

            if (pos.getX() <= -parallax.getWidth()) {
                pos.setX(pos.getX() +(2 * parallax.getWidth()));
            }
        }
    }
}