/*
** EPITECH PROJECT, 2025
** r-type_client
** File description:
** SpriteAnimationSystem
*/

#include "SpriteAnimationSystem.hpp"

#include "components/Animation.hpp"
#include "EcsManager.hpp"
#include "components/InputPlayer.hpp"
#include "components/Sprite.hpp"

namespace ecs {

void SpriteAnimationSystem::update(EcsManager& ecs)
{
    const float deltaTime = ecs.getDeltaTime();
    for (auto& entity : ecs.getEntitiesWithComponent<Sprite>()) {
        auto sprite = entity->getComponent<Sprite>();
        auto anim = entity->getComponent<Animation>();
        auto inputPlayer = entity->getComponent<InputPlayer>();

        if (!anim || !sprite || inputPlayer)
            continue;
        anim->updateAnimation(deltaTime);
        int const left = anim->getOffsetX()  + ( anim->getAnimFrame() * anim->getSpriteSize().first);
        sprite->setTextureRect(left, 0 ,  anim->getSpriteSize().first,  anim->getSpriteSize().second);
    }
}

}