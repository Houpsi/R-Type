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
    void BackgroundSystem::update(EcsManager &ecs)
    {
        for (const auto& entity : _entity) {
                auto pos = ecs.getComponentManager().getComponent<Position>(entity);
                auto parallax = ecs.getComponentManager().getComponent<Background>(entity);

                if (pos.getX() <= -parallax.getWidth()) {
                    pos.setX(pos.getX() +(2 * parallax.getWidth()));
                }
        }
    }
}// namespace ecs