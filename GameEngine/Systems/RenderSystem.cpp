/*
** EPITECH PROJECT, 2025
** R_Type
** File description:
** RenderSystem
*/

#include "RenderSystem.hpp"

void RenderSystem::update(EcsManager &ecs)
{
    _window.clear(sf::Color::Black);
    auto entities = ecs.getEntitiesWithComponent<Sprite>();
    for (const auto& entity : entities) {
        auto spriteComp = entity->getComponent<Sprite>();
        auto positionComp = entity->getComponent<Position>();
        if (spriteComp) {
            auto sprite = spriteComp->getSprite();
            if (positionComp) {
                //std::cout << positionComp->getX() << positionComp->getY() << std::endl;
                sprite.setPosition(positionComp->getX(), positionComp->getY());
            }
            _window.draw(sprite);
        }
    }
    _window.display();
}