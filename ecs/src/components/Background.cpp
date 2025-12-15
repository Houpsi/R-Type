/*
** EPITECH PROJECT, 2025
** R_Type
** File description:
** Background
*/


#include "Background.hpp"

namespace ecs {
    bool Background::getIsLooping() const 
    {
        return _isLooping;
    }

    float Background::getWidth() const 
    {
        return _width;
    }


}// namespace ecs