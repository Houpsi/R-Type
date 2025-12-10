/*
** EPITECH PROJECT, 2025
** r-type_client
** File description:
** PlayerAnimationSystem
*/

#include "PlayerAnimationSystem.hpp"

#define SIZE_X_PLAYER 33
#define SIZE_Y_PLAYER 17

namespace ecs {

void PlayerAnimationSystem::update(EcsManager& ecs)
{
    const float deltaTime = ecs.getDeltaTime();

    for (const auto & entity : ecs.getEntitiesWithComponent<InputPlayer>()) {
        const auto player  = entity->getComponent<InputPlayer>();
        const auto sprite = entity->getComponent<Sprite>();
        auto anim   = entity->getComponent<Animation>();

        if (!sprite || !player || !anim)
            continue;

        player->updateAnimation(deltaTime);
        int const animFrame = player->getAnimFrame();
        const int playerId = player->getId();
        int x = 0;

        if (player->getUp()) {
            if (animFrame == 0) {
                x = 2 * SIZE_X_PLAYER;
            }
            else if (animFrame == 1) {
                x = 3 * SIZE_X_PLAYER;
            } else {
                x = 4 * SIZE_X_PLAYER;
            }
        } else if (player->getDown()) {
            if (animFrame == 0) {
                x = 2 * SIZE_X_PLAYER;
            }
            else if (animFrame == 1) {
                x = 1 * SIZE_X_PLAYER;
            } else {
                x = 0;
            }
        } else {
            x = 2 * SIZE_X_PLAYER;
        }
        sprite->setTextureRect(x, playerId * SIZE_Y_PLAYER,SIZE_X_PLAYER, SIZE_Y_PLAYER);
    }
}

}