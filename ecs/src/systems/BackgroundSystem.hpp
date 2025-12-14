/*
** EPITECH PROJECT, 2025
** R_Type
** File description:
** BackgroundSystem
*/


#ifndef R_TYPE_BACKGROUNDSYSTEM_HPP
#define R_TYPE_BACKGROUNDSYSTEM_HPP
#include "System.hpp"

namespace ecs {
    /**
     * @class BackgroundSystem
     * @brief System responsible for the infinite scrolling logic of the background.
     *
     */
    class BackgroundSystem : public System
    {
        public:
            BackgroundSystem() = default;
            ~BackgroundSystem() override= default;
            /**
             * @brief Main update loop for the background logic.
             * @param ecs Reference to the central EcsManager to access entities and components.
             */
            void update(EcsManager& ecs) override;
    };
}



#endif// R_TYPE_BACKGROUNDSYSTEM_HPP
