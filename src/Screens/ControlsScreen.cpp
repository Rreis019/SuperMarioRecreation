#include "ControlsScreen.h"
#include "World.h"
#include "KeyGui.h"
#include "ScreenManager.h"
#include "PlayerControlsScreen.h"

void ControlsScreen::events(SDL_Event events)
{
    keyGui.events(events);
}

void ControlsScreen::render()
{
    world.render();
    screenManager.sprites[0].draw(110,15);
    keyGui.begin(150, 115);


    if(keyGui.button("1 PLAYER"))
    {
        playerControlsIndex = 0;
        screenManager.changeScreen(PLAYER_CONTROLS_SCREEN);
    }


    if(keyGui.button("2 PLAYER"))
    {
        playerControlsIndex = 1;
        screenManager.changeScreen(PLAYER_CONTROLS_SCREEN);
    }

    if(keyGui.button("BACK"))
    {
        screenManager.changeScreen(OPTIONS_SCREEN);
    }


    keyGui.end();
}

void ControlsScreen::onChangeScene()
{
    
    keyGui.currentIndex = 0;

}