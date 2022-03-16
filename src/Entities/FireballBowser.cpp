#include "FireballBowser.h"
#include "Controller.h"
#include "Timer.h"

void FireballBowser::onStart()
{
    this->startSprite = this->sprite;
    this->lifeTime = 3.0f;
}

void FireballBowser::onUpdate()
{
    this->sprite = this->startSprite + ANIMATION(0,3,200);
    this->pos.x += (120.0f * timer.deltaTime)*-1;
    this->lifeTime -= timer.deltaTime;
    if(this->lifeTime <= 0)
    {
        this->isAlive = false;
    }
}

bool FireballBowser::onColide(Ent* ent,int colIndex)
{
    if(ent->tag == ETags::TController){
        Controller* controller = (Controller*)ent;
        controller->takeDamage();
        this->isAlive = false;
    }
    return true;
}

