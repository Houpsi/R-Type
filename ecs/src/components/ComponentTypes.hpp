/*
** EPITECH PROJECT, 2026
** R_Type
** File description:
** ComponentTypes
*/

#ifndef R_TYPE_COMPONENTTYPES_HPP
#define R_TYPE_COMPONENTTYPES_HPP

#include <utility>
#include <memory>
#include "components/collision//Collision.hpp"
#include "SFML/Audio/Sound.hpp"
#include "SFML/Audio/SoundBuffer.hpp"

namespace ecs {
    namespace types {
        struct Animation {
            std::pair<int, int> _sizeSprite;
            int _offsetX;
            int _animFrame;
            float _animTimer;
            float _animSpeed;
            int _numberFrame;
        };

        struct Background {
            bool _isLooping;
            float _width;
        };

        struct Collision {
            TypeCollision _typeCollision;
            bool _isTrigger;
            float _height;
            float _width;
        };

        struct Destroy {};

        struct Enemy {
            [[maybe_unused]] int _id;
            int _type;
        };

        struct Health {
            int _health;
        };

        struct InputPlayer {
            bool _up;
            bool _down;
            bool _left;
            bool _right;
            bool _spacebar;
            bool _r;
        };

        struct PlayerAnimation {
            std::size_t _id;
            int _animFrame;
            float _animTimer;
            float _animSpeed;
        };

        struct Shoot {
            float _cooldown;
            int _damage;
            float _timeSinceLastShot;
        };

        struct Sound {
            std::unique_ptr<sf::Sound> _sound;
            sf::SoundBuffer _buffer;
        };

        struct Sprite {
            sf::Sprite _sprite;
            sf::Vector2f _scale;
        };

        struct Velocity {
            float _velocity;
            int _direction;
        };

        struct Position {
            float x;
            float y;
        };
    }
}

#endif //R_TYPE_COMPONENTTYPES_HPP
