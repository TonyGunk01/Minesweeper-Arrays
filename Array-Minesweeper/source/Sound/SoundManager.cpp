#include "../../header/Sound/SoundManager.h"
#include <iostream>

using namespace std;
using namespace sf;

namespace Sounds
{
    string SoundManager::button_click_path = "assets/sounds/button_click_sound.wav";
    string SoundManager::flag_sound_path = "assets/sounds/flag_sound.wav";
    string SoundManager::explosion_sound_path = "assets/sounds/explosion_sound.wav";
    string SoundManager::game_won_sound_path = "assets/sounds/game_won_sound.wav";
    string SoundManager::background_path = "assets/sounds/background_music.mp3";

    Music SoundManager::backgroundMusic;
    SoundBuffer SoundManager::bufferButtonClick;
    SoundBuffer SoundManager::bufferFlagSound;
    SoundBuffer SoundManager::bufferExplosion;
    SoundBuffer SoundManager::bufferGameWon;
    Sound SoundManager::soundEffect;

    float SoundManager::backgroundMusicVolume = 8.0f;

    void SoundManager::Initialize()
    {
        LoadBackgroundMusicFromFile();
        LoadSoundFromFile();
    }

    void SoundManager::LoadBackgroundMusicFromFile()
    {
        if (!backgroundMusic.openFromFile(background_path))
            cerr << "Error loading background music file: " << background_path << endl;
    }

    void SoundManager::LoadSoundFromFile()
    {
        if (!bufferButtonClick.loadFromFile(button_click_path))
            cerr << "Error loading sound file: " << button_click_path << endl;

        if (!bufferFlagSound.loadFromFile(flag_sound_path))
            cerr << "Error loading sound file: " << flag_sound_path << endl;

        if (!bufferExplosion.loadFromFile(explosion_sound_path))
            cerr << "Error loading sound file: " << explosion_sound_path << endl;

        if (!bufferGameWon.loadFromFile(game_won_sound_path))
            cerr << "Error loading sound file: " << game_won_sound_path << endl;
    }

    void SoundManager::PlaySound(SoundType soundType)
    {
        switch (soundType)
        {
            case SoundType::BUTTON_CLICK:
                soundEffect.setBuffer(bufferButtonClick);
                break;

            case SoundType::FLAG:
                soundEffect.setBuffer(bufferFlagSound);
                break;

            case SoundType::EXPLOSION:
                soundEffect.setBuffer(bufferExplosion);
                break;

            case SoundType::GAME_WON:
                soundEffect.setBuffer(bufferGameWon);
                break;

            default:
                cerr << "Invalid sound type" << endl;
                return;
        }

        soundEffect.play();
    }

    void SoundManager::PlayBackgroundMusic()
    {
        backgroundMusic.setLoop(true);
        backgroundMusic.setVolume(backgroundMusicVolume);
        backgroundMusic.play();
    }
}