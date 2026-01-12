/*
** EPITECH PROJECT, 2025
** r-type_client
** File description:
** PlayerAnimationSystem
*/

#include "PlayerAnimationSystem.hpp"

#include "components/playerAnimation/PlayerAnimation.hpp"

constexpr int  SIZE_X_PLAYER = 33;
constexpr int SIZE_Y_PLAYER = 17;

namespace ecs {

void PlayerAnimationSystem::update(EcsManager& ecs)
{
    const float deltaTime = ecs.getDeltaTime();

    for (const auto & entity : _entity) {
        const auto player = ecs.getComponentManager().getComponent<InputPlayer>(entity);
        auto sprite = ecs.getComponentManager().getComponent<Sprite>(entity);
        auto anim = ecs.getComponentManager().getComponent<PlayerAnimation>(entity);

        // if (!sprite || !player || !anim)
        //     continue;

        anim.updateAnimation(deltaTime, player.getDown(), player.getUp());
        int const animFrame = anim.getAnimFrame();
        const int playerId = anim.getId();
        int x = 0;

        if (player.getUp()) {
            if (animFrame == 0) {
                x = 2 * SIZE_X_PLAYER;
            }
            else if (animFrame == 1) {
                x = 3 * SIZE_X_PLAYER;
            } else {
                x = 4 * SIZE_X_PLAYER;
            }
        } else if (player.getDown()) {
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
        sprite.setTextureRect(x, playerId * SIZE_Y_PLAYER,SIZE_X_PLAYER, SIZE_Y_PLAYER);
    }
}

}