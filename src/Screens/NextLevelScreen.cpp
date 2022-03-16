#include "NextLevelScreen.h"
#include "ScreenManager.h"
#include "Game.h"
#include "LevelManager.h"
#include "CustomFont.h"
#include <sstream>
#include "World.h"
#include "Hud.h"
#include "Logger.h"



#include "Sprite.h"
NextLevelScreen::~NextLevelScreen()
{
    log("NextLevelScreen destructor called\n");
}

void NextLevelScreen::events(SDL_Event events){}
void NextLevelScreen::render()
{
    defaultFont.draw(153,74,displayName);
    std::stringstream ss; ss << "x  " << hud.lifes;
    defaultFont.draw(190,94,ss.str());
    if(world.maxPlayers == 1) {  sprites[1].draw(160,90); }
    else if(world.maxPlayers == 2) { 
         sprites[1].draw(150,90);
         sprites[2].draw(168,89);
    }
    sprites[0].draw(130,120);

    if(SDL_GetTicks() > nextLevelTime + DELAY_NEXT_LEVEL) {
        screenManager.changeScreen(GAME_SCREEN);
    }

}
void NextLevelScreen::onChangeScene()
{
    Mix_HaltMusic();
    displayName = "WORLD ";
    nextLevelTime = SDL_GetTicks();

    //loop through all sprites and destroy texture
    for(int i = 0; i < sprites.size(); i++)
    {
        SDL_DestroyTexture(sprites[i].texture);
    }
    sprites.clear();

    char levelFrameName[100];  
    sprintf(levelFrameName, "Resources/Levels/Level%d.png", levelManager.currentLevel+1);

    char levelConfig[100];  
    sprintf(levelConfig, "Resources/Levels/Level%d.cfg", levelManager.currentLevel+1);
    FILE *file = fopen(levelConfig, "r");
    if(file == NULL) {
        log("Error opening level config file\n");
        return;
    }
    else{
        char buffer[100];
        char name[32];
        int maxtime = 0;
        fscanf(file, "%s",name);
        fscanf(file, "%f", &hud.countdownTimerMax);
        levelManager.displayName = name;
        hud.countdownTimer = hud.countdownTimerMax;
        displayName += name;
    }
    fclose(file);


    char marioIconName[] = "Resources/Controller/Mario/icon.png";
    char luigiIconName[] = "Resources/Controller/Luigi/icon.png";
    sprites.push_back( Sprite(levelFrameName));
    sprites.push_back( Sprite(marioIconName,{0,108,248}));
    sprites.push_back( Sprite(luigiIconName,{0,108,248}));
}