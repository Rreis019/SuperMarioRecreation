#include "GameScreen.h"
#include "World.h"
#include "LevelManager.h"
#include "Input.h"
#include "Game.h"
#include "Drawings.h"
#include "KeyGui.h"
#include "ScreenManager.h"
#include "Hud.h"
#include "Particle.h"

void GameScreen::events(SDL_Event events)
{
    keyGui.events(events);

    if(events.type == SDL_WINDOWEVENT)
    {
        if( events.window.event == SDL_WINDOWEVENT_FOCUS_LOST || events.window.event == SDL_WINDOWEVENT_MOVED)
        {
            game.isPaused = true;
            keyGui.setIndexZero();   
        }
    }
}
void GameScreen::render()
{
    world.update();
    world.render();
    hud.draw();

    if(isKeyPressed(SDL_SCANCODE_ESCAPE) && !game.isPaused ){game.isPaused = !game.isPaused;}

    if(game.isPaused)
    {
        SDL_Rect pauseRect;
        pauseRect.w = 150;
        pauseRect.h = 90;
        pauseRect.x = game.witdh/2 - pauseRect.w/2;
        pauseRect.y = game.height/2 - pauseRect.h/2;
        drawFilledRect(renderer,pauseRect.x, pauseRect.y, pauseRect.w, pauseRect.h, {0,0,0,255});

        keyGui.begin(pauseRect.x+47,pauseRect.y+30);
            if(keyGui.button("CONTINUE")){game.isPaused = false;}
            if(keyGui.button("EXIT")) { 
                game.isPaused = false; 
                screenManager.changeScreen(EScreen::TITLE_SCREEN);

            } 
        keyGui.end();
    }

    if(world.numPlayers <= 0){
        game.isPaused = false;
        hud.lifes -= 1;
        hud.lifes <= 0 ? screenManager.changeScreen(EScreen::SUBMIT_SCORE_SCREEN) : screenManager.changeScreen(EScreen::GAME_OVER_SCREEN);
    }
}
void GameScreen::onChangeScene()
{
    keyGui.setIndexZero();
    keyGui.icon = &screenManager.sprites[1];
    char levelName[100];
    sprintf(levelName,"Resources/Levels/Level%d.txt",levelManager.currentLevel + 1);
    levelManager.loadLevel(levelName);

}