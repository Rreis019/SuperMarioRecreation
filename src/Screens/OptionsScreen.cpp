#include "OptionsScreen.h"
#include "Game.h"
#include "SoundManager.h"
#include "KeyGui.h"
#include "ScreenManager.h"
#include "World.h"
void OptionsScreen::events(SDL_Event events)
{
    keyGui.events(events);
	if (events.type == SDL_KEYUP && events.key.keysym.sym == SDLK_ESCAPE){screenManager.changeScreen(TITLE_SCREEN);}
}
void OptionsScreen::render()
{
	world.render();
	screenManager.sprites[0].draw(110,15);
    keyGui.begin(150, 115);
		if (keyGui.toggle("FULLSCREEN", &game.isFullscreen)) { game.setFullscreen(game.isFullscreen);}
		if (keyGui.button("CONTROLS")){}
		if (keyGui.numericInt("SCALE",&game.scale, 1, 5)){game.setScale(game.scale);}
		if (keyGui.numericInt("MUSIC",&soundManager.musicVolume, 0, MAX_VOLUME)) { soundManager.setMusicVolume(soundManager.musicVolume); }
		if(keyGui.numericInt("SFX", &soundManager.sfxVolume,0,MAX_VOLUME)) { soundManager.setSFXVolume(soundManager.sfxVolume); }

	keyGui.end();
}

void OptionsScreen::onChangeScene()
{
	
}
//  keyGui = KeyGui(&defaultFont,& screenManager.sprites[1],0,20);