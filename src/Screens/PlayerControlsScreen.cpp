#include "PlayerControlsScreen.h"
#include "KeyGui.h"
#include "ScreenManager.h"
#include "World.h"
#include "Controller.h"
#include "Logger.h"
#include <algorithm>
#include <string>

int playerControlsIndex = 0;
PlayerControls* playerControls;
void PlayerControlsScreen::events(SDL_Event events)
{
    keyGui.events(events);
}

void PlayerControlsScreen::render()
{
    world.render();
    keyGui.begin(130, 30);

        keyGui.label("PLAYER " + std::to_string(playerControlsIndex + 1) + " CONTROLS");
        //const char* down =SDL_GetKeyName(SDL_SCANCODE_TO_KEYCODE(playerControls->down));
        //log("attack: %d\n", playerControls->attack);
        keyGui.setMenuPos(150, 65);
        keyGui.inputKey("DOWN",playerControls->down);
        keyGui.inputKey("LEFT",playerControls->left);
        keyGui.inputKey("RIGHT",playerControls->right);
        keyGui.inputKey("JUMP",playerControls->jump);
        keyGui.inputKey("SHOOT",playerControls->attack);
        keyGui.inputKey("RUN",playerControls->run);
        if(keyGui.button("BACK")){
            screenManager.changeScreen(INPUT_CONTROLS_SCREEN);
        }
   keyGui.end();
}
void PlayerControlsScreen::onChangeScene()
{
    if(playerControlsIndex == 1){
        playerControls = &player1Controls;
    }
    else{
        playerControls = &player2Controls;
    }
}