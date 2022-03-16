#include  <stdio.h>  
#include "SoundManager.h"
#include "Logger.h"

#define MUSIC_PATH "Resources/Sounds/Music/"
#define SFX_PATH "Resources/Sounds/SFX/"

SoundManager soundManager;

void finnishedMusic(){log("Music finished\n");}

void SoundManager::init()
{
    if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
    {
        log("SDL_mixer Error: %s\n", Mix_GetError());
        return;
    }
    Mix_HookMusicFinished(finnishedMusic);
    this->setMusicVolume(this->musicVolume);
    this->setSFXVolume(this->sfxVolume);
}

void SoundManager::playMusic(std::string musicName,int loops)
{
    Mix_FreeMusic(currentMusic);
    std::string musicPath = MUSIC_PATH + musicName;
    currentMusic = Mix_LoadMUS(musicPath.c_str());
    currentMusicName = musicName;
    Mix_PlayMusic(currentMusic,loops);
}

void SoundManager::playSFX(std::string soundName,int loops)
{
    Mix_FreeChunk(currentSFX);
    std::string sfxPath = SFX_PATH + soundName;
    currentSFX = Mix_LoadWAV(sfxPath.c_str());
    if(currentSFX == nullptr){ printf("Failed to load sfx! SDL_mixer Error: %s\n", Mix_GetError()); }
    Mix_PlayChannel(0, currentSFX, loops);
}

void SoundManager::stopMusic(){Mix_HaltMusic();}

void SoundManager::setMusicVolume(int volume)
{
    this->musicVolume = volume;

    if(musicVolume > MAX_VOLUME){ this->musicVolume = MAX_VOLUME;}
    else if(musicVolume < 0){musicVolume = 0;}
    
    Mix_VolumeMusic(musicVolume * 4.26F);
}

void SoundManager::setSFXVolume(int volume)
{
    this->sfxVolume = volume;

    if(sfxVolume > MAX_VOLUME){ this->sfxVolume = MAX_VOLUME;}
    else if(sfxVolume < 0){sfxVolume = 0;}

    Mix_Volume(0,sfxVolume * 4.26F);
}

//free the memory
void SoundManager::destroy(){
    Mix_FreeMusic(currentMusic);
    Mix_FreeChunk(currentSFX);
    Mix_CloseAudio();
}