/*
** EPITECH PROJECT, 2026
** r-type_client
** File description:
** Score
*/
#include "Score.hpp"

namespace ecs {

    void Score::addToScore(uint32_t points)
    {
        _score += points;
    }

    void Score::setScore(uint32_t score)
    {
        _score = score;
    }

    uint32_t Score::getScore() const
    {
        return _score;
    }

} // ecs