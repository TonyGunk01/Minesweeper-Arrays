#pragma once
#include <SFML/Audio.hpp>
#include <string>

using namespace sf;
using namespace std;

namespace Sounds
{
    enum class SoundType
    {
        BUTTON_CLICK,
        FLAG,
        EXPLOSION,
        GAME_WON
    };

    class SoundManager
    {
        private:
            static Music backgroundMusic;
            static SoundBuffer bufferButtonClick;
            static SoundBuffer bufferFlagSound;
            static SoundBuffer bufferExplosion;
            static SoundBuffer bufferGameWon;
            static Sound soundEffect;
            static float backgroundMusicVolume;

            static string button_click_path;
            static string flag_sound_path;
            static string explosion_sound_path;
            static string game_won_sound_path;

            static string background_path;

            static void LoadBackgroundMusicFromFile();
            static void LoadSoundFromFile();

        public:
            // Initialization and loading functions
            static void Initialize();
            static void PlaySound(SoundType soundType);
            static void PlayBackgroundMusic();
    };
}