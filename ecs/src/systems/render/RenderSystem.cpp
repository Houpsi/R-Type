/*
** EPITECH PROJECT, 2025
** r-type_client
** File description:
** RenderSystem
*/

#include "RenderSystem.hpp"

namespace ecs {
    void RenderSystem::update(EcsManager &ecs)
    {
        _window.clear(sf::Color::Black);

        for (const auto& entity : _entities) {
            auto spriteComp = ecs.getComponent<Sprite>(entity);
            auto positionComp = ecs.getComponent<Position>(entity);
            // if (spriteComp) {
                auto sprite = spriteComp.getSprite();
                // if (positionComp) {
                    sprite.setPosition({positionComp.getX(), positionComp.getY()});
                // }
                _window.draw(sprite);
            // }
        }
        _window.display();
    }

    void RenderSystem::configure(EcsManager &ecs)
    {
        _targetSignature.set(ecs.getComponentType<Sprite>());
        _targetSignature.set(ecs.getComponentType<Position>());
    }

} // namespace ECS
