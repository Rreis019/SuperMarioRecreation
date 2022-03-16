#include "GameOverScreen.h"
#include "KeyGui.h"
#include "ScreenManager.h"
#include "Timer.h"
#include "Input.h"
#include "World.h"
#include "Hud.h"
#include "SaveSystem.h"
#include "LevelManager.h"
#include "ScoreSave.h"
#include "SoundManager.h"


#include "Game.h"

#include "TextBox.h"
#include "Button.h"

EGameOverType gameOverType = EGameOverType::GameOver;

GameOverScreen::GameOverScreen()
{

}

void GameOverScreen::events(SDL_Event events)
{
    keyGui.events(events);
}

void GameOverScreen::render()
{
    if(gameOverType == EGameOverType::GameOver)
		this->sprites[0].draw(160, 70);//GAMEOVER TEXTO
	else if(gameOverType == EGameOverType::TimeUp)
		this->sprites[1].draw(170, 70);//TIME IS UP

    keyGui.begin(167, 110);

    if(keyGui.button("CONTINUE"))
    {
        game.isPaused = false;
        gameOverType = EGameOverType::GameOver;
        screenManager.changeScreen(EScreen::NEXT_LEVEL_SCREEN);
    }

    if(keyGui.button("QUIT"))
    {
        game.isPaused = false;
        gameOverType = GameOver;
        screenManager.changeScreen(EScreen::TITLE_SCREEN);
    }

    if(isKeyPressed(SDL_SCANCODE_DOWN) || isKeyPressed(SDL_SCANCODE_UP))
    {
        if(keyGui.icon == nullptr){
            flickTime = timer.startTick;
            drawHand = true;
            keyGui.icon = &screenManager.sprites[3];
        }
    }

    if (timer.startTick > flickTime + 500)
	{
		drawHand = !drawHand;
		flickTime = timer.startTick;
		keyGui.icon = drawHand ? &screenManager.sprites[3] : nullptr;
	}

    keyGui.end();
}

void GameOverScreen::onChangeScene()
{
    //hud.lifes -= 1;

    soundManager.playMusic("game Over.mp3",1);
    SaveData data;
    data.CurrentLevel = levelManager.currentLevel;
    data.Lives = hud.lifes;
    data.Score = hud.getScore();
    data.CurrentCoins = hud.getCoin();
    saveSystem.save(saveSystem.currentSaveSlot, data);

    if(this->sprites.size() == 0){
        loadMultipleImages(sprites, "Resources/Screens/GameOver/", "GameOver_");
    }

    keyGui.currentFont = &defaultFont;
    keyGui.marginY = 20;
    keyGui.icon =  &screenManager.sprites[3];
    keyGui.iconX = -20;
}

void GameOverScreen::onChangedResolution()
{

}
