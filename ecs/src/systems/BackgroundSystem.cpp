/*
** EPITECH PROJECT, 2025
** R_Type
** File description:
** BackgroundSystem
*/

#include "BackgroundSystem.hpp"
#include "components/Position.hpp"
#include "EcsManager.hpp"
#include "components/Background.hpp"

namespace ecs {
    void BackgroundSystem::update(EcsManager &ecs)
    {
        for (const auto& entity : ecs.getEntitiesWithComponent<Background>()) {
                auto pos = entity->getComponent<Position>();
                auto parallax = entity->getComponent<Background>();

                if (pos->getX() <= -parallax->getWidth()) {
                    pos->setX(pos->getX() +(2 * parallax->getWidth()));
                }
        }
    }
}// namespace ecs