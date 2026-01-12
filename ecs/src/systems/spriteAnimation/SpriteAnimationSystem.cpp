/*
** EPITECH PROJECT, 2025
** r-type_client
** File description:
** SpriteAnimationSystem
*/

#include "SpriteAnimationSystem.hpp"

#include "components/animation/Animation.hpp"
#include "managers/EcsManager.hpp"
#include "components/inputPlayer/InputPlayer.hpp"
#include "components/sprite/Sprite.hpp"

namespace ecs {

void SpriteAnimationSystem::update(EcsManager& ecs)
{
    const float deltaTime = ecs.getDeltaTime();
    for (auto& entity : _entity) {
        auto sprite = ecs.getComponentManager()<Sprite>->get(entity);
        auto anim = ecs.getComponentManager()<Animation>->get(entity);
        auto inputPlayer = ecs.getComponentManager()<InputPlayer>->get(entity);

        if (inputPlayer|| !anim || !sprite) {
                continue;
        }
        anim->updateAnimation(deltaTime);
        int const left = anim->getOffsetX()  + ( anim->getAnimFrame() * anim->getSpriteSize().first);
        sprite->setTextureRect(left, 0 ,  anim->getSpriteSize().first,  anim->getSpriteSize().second);
    }
}

}