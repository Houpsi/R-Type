/*
** EPITECH PROJECT, 2026
** r-type_client
** File description:
** Score
*/

#ifndef R_TYPE_CLIENT_SCORE_HPP
#define R_TYPE_CLIENT_SCORE_HPP
#include "Component.hpp"
#include <cstdint>

namespace ecs {

    class Score: public Component {
    public:
        void addToScore(uint32_t points);
        void setScore(uint32_t score);
        [[nodiscard]] uint32_t getScore() const;

    private:
        uint32_t _score = 0;
    };
} // ecs

#endif //R_TYPE_CLIENT_SCORE_HPP