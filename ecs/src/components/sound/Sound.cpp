/*
** EPITECH PROJECT, 2025
** r-type_client
** File description:
** Sound
*/

#include "Sound.hpp"

namespace ecs {
    /**
     * @bried Load the sound from a file
     * @param filepath The path to the sound file
     */
    Sound::Sound(const std::string& filepath)
    {
        if (!_buffer.loadFromFile(filepath))
            throw std::runtime_error("Failed to load sound: " + filepath);
        _sound = std::make_unique<sf::Sound>(_buffer);
        _sound->setVolume(100.f);
    }

    /**
     * @brief Gets Sound of the component
     * @return the sound of the component
     */
    const sf::Sound& Sound::getSound() const
    {
        return *_sound;
    }

    /**
     * @brief PLay the sound of the component
     */
    void Sound::play()
    {
        if (_sound) {
            if (_sound->getStatus() == sf::Sound::Status::Playing) {
                _sound->stop();
            }
            _sound->play();
        }
    }
}