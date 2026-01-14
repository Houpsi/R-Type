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
    for (auto& entity : _entities) {
        auto sprite = ecs.getComponent<Sprite>(entity);
        auto anim = ecs.getComponent<Animation>(entity);
        auto inputPlayer = ecs.getComponent<InputPlayer>(entity);

        // if (inputPlayer|| !anim || !sprite) {
        //         continue;
        // }
        anim.updateAnimation(deltaTime);
        int const left = anim.getOffsetX()  + ( anim.getAnimFrame() * anim.getSpriteSize().first);
        sprite.setTextureRect(left, 0 ,  anim.getSpriteSize().first,  anim.getSpriteSize().second);
    }
}

    void SpriteAnimationSystem::configure(EcsManager &ecs)
    {
        _targetSignature.set(ecs.getComponentType<Sprite>());
        _targetSignature.set(ecs.getComponentType<Animation>());
        _targetSignature.set(ecs.getComponentType<InputPlayer>());
    }
}