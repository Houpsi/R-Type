/*
** EPITECH PROJECT, 2026
** r-type_client
** File description:
** Score
*/
#include "Score.hpp"

namespace ecs
{
    void Score::addToScore(int v)
    {
        _score += v;
    }

    void Score::setScore(int v)
    {
        _score = v;
    }

    int Score::getScore() const
    {
        return _score;
    }
} // ecs