#include "Sack.h"
#include "Controller.h"
#include "Timer.h"
#include "World.h"
#include "Prefabs.h"
#include "Toad.h"
#include "SoundManager.h"

void Sack::onStart()
{
    this->startSprite = this->sprite;
    this->tag = ETags::TSack;
}

void Sack::onUpdate()
{
    switch (this->currentAnimation)
    {
    case ESackAnimation::ESack_None:
        break;
    case ESackAnimation::ESack_Idle:
        this->sprite = this->startSprite + ANIMATION(0,2,200);
        if(this->timeNextAnimation <= 0){
            this->timeNextAnimation = 0.3f * 4;
            this->currentAnimation = ESackAnimation::ESack_Open;
        }
        break;
    case ESackAnimation::ESack_Open:
        int index = ANIMATION(2,4,300);
        this->sprite = this->startSprite + index;
        if(index == 5){
            this->currentAnimation = ESackAnimation::ESack_None;
            Toad* toad = new Toad(&enemySprites[60]);
            toad->pos = this->pos;
            world.addEntity(toad);
            soundManager.playMusic("13.world Clear.mp3");
        }
        break;
    }

    timeNextAnimation -= timer.deltaTime;
}

bool Sack::onColide(Ent* ent,int colIndex)
{
    if(ent->tag == TToad){return false;}
    if(ent->tag != TController || colided){ return false;}

    Controller* c = (Controller*)ent;
    c->freeze();
    c->gravity = false;
    c->changeSprite(0);
    colided = true;
    this->currentAnimation = ESack_Idle;
    timeNextAnimation = 0.5f;

    return false;
}