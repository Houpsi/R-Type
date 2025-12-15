/*
** EPITECH PROJECT, 2025
** R_Type
** File description:
** Background
*/

#ifndef R_TYPE_BACKGROUND_HPP
#define R_TYPE_BACKGROUND_HPP
#include "Component.hpp"

namespace ecs {
    /**
     * @class Background
     * @brief A component handling background logic, specifically for scrolling/looping effects.
     */
    class Background : public Component
    {
        public:
            /**
             * @brief Construct a new Background object.
             *
             * @param width The width of the sprite/texture used for the background.
             * This defines the point at which the background should loop.
             */
            explicit Background(float witdh) :  _width(witdh) {};
            ~Background() override = default;
            float getWidth() const;
            bool getIsLooping() const;
        private:
            bool _isLooping = true;
            float _width;
    };
}



#endif// R_TYPE_BACKGROUND_HPP
