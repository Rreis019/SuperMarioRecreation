#include "PlayerControlsScreen.h"
#include "KeyGui.h"
#include "ScreenManager.h"

int playerControlsIndex = 0;

void PlayerControlsScreen::events(SDL_Event events)
{
    keyGui.events(events);
}

void PlayerControlsScreen::render()
{
    keyGui.begin(130, 30);

        keyGui.label("PLAYER " + std::to_string(playerControlsIndex + 1) + " CONTROLS");


        keyGui.setMenuPos(170, 65);
        keyGui.button("DOWN");
        keyGui.button("LEFT");
        keyGui.button("RIGHT");
        keyGui.button("JUMP");
        keyGui.button("SHOOT");
        keyGui.button("RUN");
        if(keyGui.button("BACK")){
            screenManager.changeScreen(INPUT_CONTROLS_SCREEN);
        }
   keyGui.end();
}
void PlayerControlsScreen::onChangeScene()
{
    
}