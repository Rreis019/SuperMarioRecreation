#pragma once
#include <vector>
#include <string>
#include <SDL2/SDL_mixer.h>

#define MAX_VOLUME 30
class SoundManager
{
    public:
        void init();
        Mix_Music* loadMusic(std::string musicName);
        void playMusic(std::string musicName,int loops = 1);
        void playSFX(std::string soundName,int loops = 0);

        void stopMusic();
        void stopMusic(Mix_Music* music);
        void destroy(Mix_Music* music);
        void destroy();
        
        void setMusicVolume(int volume);
        void setSFXVolume(int volume);
        bool isPlayingMusic = false;
        bool isPlayingSFX = false;

        int musicVolume = 1;
        int sfxVolume   = 1;
        std::string currentMusicName = "";
    private:
        Mix_Chunk* currentSFX   = nullptr;
        Mix_Music* currentMusic = nullptr;
};

extern SoundManager soundManager;