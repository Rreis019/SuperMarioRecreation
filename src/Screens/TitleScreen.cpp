#include "TitleScreen.h"
#include "Game.h"
#include "KeyGui.h"
#include "ScreenManager.h"
#include "LevelManager.h"
#include <Windows.h>

#include "World.h"

void TitleScreen::events(SDL_Event events)
{
    keyGui.events(events);
}
void TitleScreen::render()
{
    world.render();
    screenManager.sprites[0].draw(110,15);
    keyGui.begin(150, 125);

    if(keyGui.button("1 PLAYER GAME")) { world.maxPlayers = 1; screenManager.changeScreen(NEW_GAME_SCREEN); }
    if(keyGui.button("2 PLAYER GAME")) { world.maxPlayers = 2; screenManager.changeScreen(NEW_GAME_SCREEN);}
    if(keyGui.button("SCOREBOARD")) { screenManager.changeScreen(SCOREBOARD_SELECTION_SCREEN); }
    if(keyGui.button("OPTIONS")) { screenManager.changeScreen(OPTIONS_SCREEN); }

    keyGui.end();
}
void TitleScreen::onChangeScene()
{
    std::string titleLevelPath = "Resources/Levels/TitleScreen.txt";
    if(titleLevelPath != levelManager.levelPath)
    {
        world.numPlayers = 0;
        world.maxPlayers = 0;
     levelManager.loadLevel("Resources/Levels/TitleScreen.txt");
    } 
    keyGui = KeyGui(&defaultFont,& screenManager.sprites[1],0,20);
}