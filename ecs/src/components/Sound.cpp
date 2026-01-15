/*
** EPITECH PROJECT, 2025
** r-type_client
** File description:
** Sound
*/

#include "Sound.hpp"
namespace ecs {
    void Sound::setIsPlayed(bool played)
    {
        _isPlayed = played;
    }

    bool Sound::getIsPlayed() const {
        return _isPlayed;
    }

    int Sound::getIdMusic() const {
        return _idMusic;
    }

    int Sound::getIsLoopping()
    {
        return _isLooping;
    }

    void Sound::setIsLoopping(bool loop)
    {
        _isLooping = loop;
    }
};  //namespace ecs