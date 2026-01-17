/*
** EPITECH PROJECT, 2026
** r-type_client
** File description:
** Score
*/

#ifndef R_TYPE_CLIENT_SCORE_HPP
    #define R_TYPE_CLIENT_SCORE_HPP
#include "Component.hpp"

namespace ecs
{
    class Score: public Component {
    public:
        Score(): _score(0) {};
        void addToScore(int v);
        void setScore(int v);
        int getScore() const;

    private:
        int _score = 0;
    };
} // ecs

#endif //R_TYPE_CLIENT_SCORE_HPP