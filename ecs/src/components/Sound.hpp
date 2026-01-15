/*
** EPITECH PROJECT, 2025
** r-type_client
** File description:
** Sound
*/

#ifndef BOOTSTRAP_SOUND_HPP
    #define BOOTSTRAP_SOUND_HPP
#include "Component.hpp"


namespace ecs {

    class Sound : public Component {
      public:
        explicit Sound(int id, bool loop): _idMusic(id) , _isLooping(loop) {};
        ~Sound() override = default;
        void setIsPlayed(bool played);
        bool getIsPlayed() const;
        int getIdMusic() const;
        void setIsLoopping(bool loop);
        int getIsLoopping();


        private:
            int _idMusic;
            bool _isPlayed = false;
            bool _isLooping = false;
    };
}

#endif //BOOTSTRAP_SOUND_HPP