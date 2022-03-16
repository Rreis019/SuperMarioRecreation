#include "Hud.h"
#include "Utils.h"
#include "CustomFont.h"
#include "Timer.h"
#include "LevelManager.h"
#include "ScreenManager.h"
#include "GameOverScreen.h"
#include "Game.h"
#include "Logger.h"

#define LIMIT_COIN  99
#define LIMIT_SCORE 999999

Hud hud = Hud();

void Hud::init()
{

    loadSpriteSheet(coinSprites,"Resources/Fonts/HudCoin.png");
}

void Hud::draw()
{
    if(countdownTimer > countdownTimerMax){
        countdownTimer = countdownTimerMax;
    }


    int x = 80;
    int y = 17; 

    defaultFont.draw(x,y,"MARIO");
    defaultFont.draw(x,y+11,scoreStr);

    int coinIndex = ANIMATION(0,3,300);
    coinSprites[coinIndex].draw(x+65,y+11);
    defaultFont.draw(x+65+10,y+11,coinStr);


    defaultFont.draw(x+115,y,"WORLD");
    int levelW = defaultFont.getTextW(levelManager.displayName);
    defaultFont.draw(x+113 + levelW/2,y+11,levelManager.displayName);


    defaultFont.draw(x+184,y,"TIME");
    defaultFont.draw(x+184+8,y+11, std::to_string((int)countdownTimer));

    if(!game.isPaused){
        countdownTimer -= timer.deltaTime;
    }
    
    if(countdownTimer < 0){
        countdownTimer = 0;
        gameOverType = EGameOverType::TimeUp;
        hud.lifes -= 1;
        hud.lifes <= 0 ? screenManager.changeScreen(EScreen::SUBMIT_SCORE_SCREEN) : screenManager.changeScreen(EScreen::GAME_OVER_SCREEN);
    }

}

void Hud::addCoin(int amount)
{
    if (this->coin == LIMIT_COIN)
		return;
    
	this->coin += amount;

    //Coin to string format
    coinStr = "x";
	if (this->coin < 10)
		coinStr += "0";
	coinStr +=  std::to_string(this->coin);
}

void Hud::setCoin(int amount)
{
    if (this->coin == LIMIT_COIN)
        return;

    this->coin = amount;
    coinStr = "x";
    if (this->coin < 10)
        coinStr += "0";
    coinStr +=  std::to_string(this->coin);
}

void Hud::addScore(int amount)
{
    if (this->score == LIMIT_SCORE)
        return;

    this->score += amount;
    log("Score: %d\n", this->score);
    //Score to string format
    int size = intLength(this->score);
	scoreStr = "";
	for (int i = 0; i < 6 - size; i++)
	{
		scoreStr += "0";
	}
    scoreStr += std::to_string(this->score);
}

void Hud::setScore(int amount){
    this->score = amount;
    scoreStr = "";
    int size = intLength(this->score);
    for (int i = 0; i < 6 - size; i++)
    {
        scoreStr += "0";
    }
    scoreStr += std::to_string(this->score);
}