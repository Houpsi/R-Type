/*
** EPITECH PROJECT, 2026
** R_Type
** File description:
** SoundManager
*/


#include "SoundManager.hpp"
#include "EcsConstant.hpp"
#include "SFML/Audio/Sound.hpp"

#include <iostream>

namespace ecs {
    void SoundManager::load(std::string_view id, const std::string& path)
    {
        sf::SoundBuffer buffer;
        if (!buffer.loadFromFile(path)) {
            throw std::runtime_error("Failed to load sound from " + path);
        }
        _buffers.emplace(id, std::move(buffer));
    }

    void SoundManager::play(int id, bool looping)
    {
        if (id < 0 || id > static_cast<int>(idToSound.size()))
            return;

        std::string_view soundName = idToSound[id - 1];

        auto it = _buffers.find(std::string(soundName));
        if (it == _buffers.end())
            return;

        auto sound = std::make_shared<sf::Sound>(it->second);
        sound->setBuffer(it->second);
        sound->setVolume(volumeMusic);
        sound->setLooping(looping);
        sound->play();

        _activeSounds.push_back(sound);
    }

    void SoundManager::update()
    {
        std::vector<std::shared_ptr<sf::Sound>> stillPlaying;

        for (auto& s : _activeSounds) {
            if (s->getStatus() != sf::Sound::Status::Stopped) {
                stillPlaying.push_back(s);
            }
        }
        _activeSounds = std::move(stillPlaying);
    }


    SoundManager::SoundManager()
    {
        loadFolder(static_cast<std::string>(folderSound));
    }

    void SoundManager::loadFolder(const std::string& folderPath)
    {
        for (auto& entry : std::filesystem::directory_iterator(folderPath)) {
            if (entry.is_regular_file()) {
                std::string path = entry.path().string();
                std::string id = entry.path().stem().string();
                load(id, path);
            }
        }
    }

}