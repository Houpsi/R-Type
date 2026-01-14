/*
** EPITECH PROJECT, 2026
** R_Type
** File description:
** SoundSystem
*/


#include "SoundSystem.hpp"
#include "components/Sound.hpp"

namespace ecs {
    void SoundSystem::update(EcsManager &ecs)
    {
        for (auto const &entity: ecs.getEntitiesWithComponent<Sound>()) {
            auto sound = entity->getComponent<Sound>();
            if (!sound->getIsPlayed()) {
                _soundManager.play( sound->getIdMusic(), sound->getIsLoopping());
                entity->removeComponent<Sound>();
                sound->setIsPlayed(true);
            }
        }
        _soundManager.update();
    }
}