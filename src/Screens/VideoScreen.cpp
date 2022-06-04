#include "VideoScreen.h"
#include "Game.h"
#include "KeyGui.h"
#include "ScreenManager.h"
#include "World.h"

VideoScreen::VideoScreen()
{

}
void VideoScreen::events(SDL_Event events)
{
    keyGui.events(events);
	if (events.type == SDL_KEYUP && events.key.keysym.sym == SDLK_ESCAPE){screenManager.changeScreen(TITLE_SCREEN);}
}
void VideoScreen::render()
{
	world.render();
	screenManager.sprites[0].draw(110,15);
    keyGui.begin(150, 115);
		if (keyGui.toggle("FULLSCREEN", &game.isFullscreen)) { game.setFullscreen(game.isFullscreen);}
		if (keyGui.numericInt("SCALE",&game.scale, 1, 5)){game.setScale(game.scale);}
        //back go to options screen
        if (keyGui.button("BACK")){screenManager.changeScreen(OPTIONS_SCREEN);}
	keyGui.end();
}

void VideoScreen::onChangeScene()
{
 	keyGui.currentIndex = 0;
}
//  keyGui = KeyGui(&defaultFont,& screenManager.sprites[1],0,20);