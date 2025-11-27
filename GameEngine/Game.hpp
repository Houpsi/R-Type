//
// Created by aleks on 27/11/2025.
//

#ifndef BOOTSTRAP_GAME_HPP
#define BOOTSTRAP_GAME_HPP
#include "EcsManager.hpp"


class Game {
    public:
        Game();
        ~Game();
        void run();
    private:
        EcsManager _ecs;

};


#endif //BOOTSTRAP_GAME_HPP