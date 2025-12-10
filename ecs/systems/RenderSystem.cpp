/*
** EPITECH PROJECT, 2025
** R_Type
** File description:
** RenderSystem
*/

#include "RenderSystem.hpp"

namespace ecs {
void RenderSystem::update(EcsManager &ecs)
{
    _window.clear(sf::Color::Black);
    auto entities = ecs.getEntitiesWithComponent<Sprite>();
    for (const auto& entity : entities) {
        auto spriteComp = entity->getComponent<Sprite>();
        auto positionComp = entity->getComponent<Position>();
        auto textComp = entity->getComponent<Score>();
        auto text = entity->getComponent<Score>()->getText();

        if (spriteComp) {
            auto sprite = spriteComp->getSprite();
            if (positionComp) {
                sprite.setPosition({positionComp->getX(), positionComp->getY()});
            }
            _window.draw(sprite);
        }
        if (textComp)
        {
            _window.draw(text);
        }
    }
    _window.display();
}
}