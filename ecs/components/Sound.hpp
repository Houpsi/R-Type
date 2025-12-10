/*
** EPITECH PROJECT, 2025
** r-type_client
** File description:
** Sound
*/

#ifndef BOOTSTRAP_SOUND_HPP
#define BOOTSTRAP_SOUND_HPP
#include <SFML/Audio.hpp>
#include "Component.hpp"

namespace ECS {
class Sound : public Component {
  public:
    Sound(const std::string& filepath);
    ~Sound() override = default;

    const sf::Sound& getSound() const;
    void play();

  private:
    std::unique_ptr<sf::Sound> _sound;
    sf::SoundBuffer _buffer;
};
}

#endif //BOOTSTRAP_SOUND_HPP