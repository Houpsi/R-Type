/*
** EPITECH PROJECT, 2025
** r-type_client
** File description:
** RenderSystem
*/

#include "RenderSystem.hpp"
#define SIZE_X_PLAYER 33
#define SIZE_Y_PLAYER 17

namespace ecs {
void RenderSystem::update(EcsManager &ecs)
{
    _window.clear(sf::Color::Black);
    const auto entities = ecs.getEntitiesWithComponent<Sprite>();

    for (const auto& entity : entities) {
        auto spriteComp = entity->getComponent<Sprite>();
        auto positionComp = entity->getComponent<Position>();
        if (spriteComp) {
            auto sprite = spriteComp->getSprite();
            if (positionComp) {
                sprite.setPosition({positionComp->getX(), positionComp->getY()});
            }
            _window.draw(sprite);
        }
    }
    _window.display();
}

} // namespace ECS
