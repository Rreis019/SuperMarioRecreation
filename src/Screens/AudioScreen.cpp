#include "AudioScreen.h"
#include "Game.h"
#include "KeyGui.h"
#include "ScreenManager.h"
#include "World.h"
#include "SoundManager.h"
AudioScreen::AudioScreen()
{

}
void AudioScreen::events(SDL_Event events)
{
    keyGui.events(events);
	if (events.type == SDL_KEYUP && events.key.keysym.sym == SDLK_ESCAPE){screenManager.changeScreen(TITLE_SCREEN);}
}
void AudioScreen::render()
{
	world.render();
	screenManager.sprites[0].draw(110,15);
    keyGui.begin(150, 115);
		if (keyGui.numericInt("MUSIC",&soundManager.musicVolume, 0, MAX_VOLUME)) { soundManager.setMusicVolume(soundManager.musicVolume); }
		if(keyGui.numericInt("SFX", &soundManager.sfxVolume,0,MAX_VOLUME)) { soundManager.setSFXVolume(soundManager.sfxVolume); }
        //back go to options screen
        if (keyGui.button("BACK")){screenManager.changeScreen(OPTIONS_SCREEN);}
	keyGui.end();
}

void AudioScreen::onChangeScene()
{
 	keyGui.currentIndex = 0;
}
//  keyGui = KeyGui(&defaultFont,& screenManager.sprites[1],0,20);