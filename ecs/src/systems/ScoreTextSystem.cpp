/*
** EPITECH PROJECT, 2026
** r-type_client
** File description:
** ScoreTextSystem
*/

#include "ScoreTextSystem.hpp"

namespace ecs
{
    void ScoreTextSystem::update(EcsManager& ecs)
    {
        for (auto& entity : ecs.getEntitiesWithComponent<Text>()) {
            auto score = entity->getComponent<Score>();
            auto text  = entity->getComponent<Text>();

            if (!score || !text) continue;

            text->setString("Score: " + std::to_string(score->getScore()));
        }
    }

}