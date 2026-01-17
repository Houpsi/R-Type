/*
** EPITECH PROJECT, 2026
** r-type_client
** File description:
** ScoreTextSystem
*/

#ifndef R_TYPE_CLIENT_SCORETEXTSYSTEM_HPP
#define R_TYPE_CLIENT_SCORETEXTSYSTEM_HPP
#include <string>

#include "EcsManager.hpp"
#include "components/Score.hpp"
#include "components/Text.hpp"

namespace ecs
{
    class ScoreTextSystem : public System {
    public:
        void update(EcsManager& ecs) override;
    };
}


#endif //R_TYPE_CLIENT_SCORETEXTSYSTEM_HPP