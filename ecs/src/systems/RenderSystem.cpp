/*
** EPITECH PROJECT, 2025
** r-type_client
** File description:
** RenderSystem
*/

#include "RenderSystem.hpp"
#include "components/Score.hpp"
#define SIZE_X_PLAYER 33
#define SIZE_Y_PLAYER 17

namespace ecs {
void RenderSystem::update(EcsManager &ecs)
{
    _window.clear(sf::Color::Black);
    const auto entities = ecs.getEntities();

    for (const auto& entity : entities) {
        auto spriteComp = entity->getComponent<Sprite>();
        auto textComp = entity->getComponent<Text>();
        auto scoreComp = entity->getComponent<Score>();
        auto positionComp = entity->getComponent<Position>();
        if (spriteComp) {
            auto sprite = spriteComp->getSprite();
            if (positionComp) {
                sprite.setPosition({positionComp->getX(), positionComp->getY()});
            }
            _window.draw(sprite);
        }
        if (textComp) {
            auto& t = textComp->getText();
            if (positionComp)
                t.setPosition({positionComp->getX(), positionComp->getY()});
            if (scoreComp) {
                t.setString("Score: " + std::to_string(scoreComp->getScore()));
            }
            _window.draw(t);
        }
    }
    _window.display();
}

} // namespace ECS
