#include "Coin.h"
#include "Hud.h"
#include "Timer.h"
#include "SoundManager.h"

void Coin::onStart()
{
    this->startSprite = this->sprite;
}

void Coin::onUpdate()
{   
    this->sprite = this->startSprite + ANIMATION(0,4,100);
}

bool Coin::onColide(Ent* ent,int colIndex)
{
    if(ent->tag != TController){return true;}

    if(!this->isAlive)
        return true;

    this->isAlive = false;
    soundManager.playSFX("Coin.wav");
    hud.addCoin(1);
    return true;
}