/*
** EPITECH PROJECT, 2026
** R_Type
** File description:
** SoundSystem
*/

#ifndef R_TYPE_SOUNDSYSTEM_HPP
#define R_TYPE_SOUNDSYSTEM_HPP
#include "EcsManager.hpp"
#include "SoundManager.hpp"

namespace ecs {
    class SoundSystem : public System {
    public:
        explicit SoundSystem() = default;
        ~SoundSystem() = default;

        void update(EcsManager& ecs);

    private:
        SoundManager _soundManager;
    };
}


#endif// R_TYPE_SOUNDSYSTEM_HPP
