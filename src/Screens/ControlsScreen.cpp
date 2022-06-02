#include "ControlsScreen.h"
#include "World.h"
#include "KeyGui.h"
#include "ScreenManager.h"

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

    }


    if(keyGui.button("2 PLAYER"))
    {

    }



    keyGui.end();
}

void ControlsScreen::onChangeScene()
{
    keyGui = KeyGui(&defaultFont,& screenManager.sprites[1],0,20);
}