/*
** EPITECH PROJECT, 2026
** R_Type
** File description:
** SoundManager
*/

#ifndef R_TYPE_SOUNDMANAGER_HPP
#define R_TYPE_SOUNDMANAGER_HPP
#include "SFML/Audio/SoundBuffer.hpp"

#include <SFML/Audio/Sound.hpp>
#include <vector>

#include <string>
#include <unordered_map>


namespace ecs {
    class SoundManager
    {
    public:
        SoundManager();
        void loadFolder(const std::string& folderPath);
        void load(std::string_view id, const std::string& path);
        void play(int id, bool loop);
        void update();

    private:
        std::unordered_map<std::string, sf::SoundBuffer> _buffers;
        std::vector<std::shared_ptr<sf::Sound>> _activeSounds;

    };
}
#endif// R_TYPE_SOUNDMANAGER_HPP
