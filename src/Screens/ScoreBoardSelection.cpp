#include "ScoreBoardSelection.h"
#include "ScoreBoardScreen.h"
#include "World.h"
#include "KeyGui.h"
#include "ScreenManager.h"
#include "LevelManager.h"

void ScoreBoardSelection::events(SDL_Event events)
{
    keyGui.events(events);
    if (events.type == SDL_KEYUP && events.key.keysym.sym == SDLK_ESCAPE)
    {
        screenManager.changeScreen(TITLE_SCREEN);
        world.maxPlayers = 0;
    }
}

void ScoreBoardSelection::render()
{
    world.render();
    screenManager.sprites[0].draw(110, 15);
    keyGui.begin(150, 125);

    if(keyGui.button("LOCAL")){
        isScoreBoardOnline = false;
        screenManager.changeScreen(SCOREBOARD_SCREEN);
    }   

    if(keyGui.button("ONLINE")){
        isScoreBoardOnline = true;
        screenManager.changeScreen(SCOREBOARD_SCREEN);
    }
    keyGui.end();
}
void ScoreBoardSelection::onChangeScene()
{
    keyGui.currentIndex = 0;
    std::string titleLevelPath = "Resources/Levels/TitleScreen.txt";
    if(titleLevelPath != levelManager.levelPath)
    {
     levelManager.loadLevel(titleLevelPath);
    } 
}
