/*
** EPITECH PROJECT, 2025
** r-type_client
** File description:
** Animation
*/


#ifndef R_TYPE_CLIENT_ANIMATION_HPP
#define R_TYPE_CLIENT_ANIMATION_HPP
#include "Component.hpp"
#include <SFML/Graphics.hpp>

namespace ECS {
class Animation : public Component {
  public:
    explicit Animation(const std::pair<int, int> size, const int offsetX, const int numberFrame) : _sizeSprite(size), _offsetX(offsetX), _numberFrame(numberFrame) {}
    void updateAnimation(float dt);
    int getAnimFrame() const ;
    int getNumberFrame() const ;
    float getAnimTimer() const ;
    void setAnimTimer(const float animTimer);
    void setAnimFrame(const int animFrame);
    float getAnimSpeed() const;
    int getOffsetX() const;
    std::pair<int,int> getSpriteSize();
  private:
    std::pair<int, int> _sizeSprite;
    int _offsetX = 0;
    int _animFrame = 0;
    float _animTimer = 0.f;
    float _animSpeed = 0.1f;
    int _numberFrame = 0;
};
}



#endif// R_TYPE_CLIENT_ANIMATION_HPP
