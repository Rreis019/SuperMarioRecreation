#include "Shell.h"
#include "Timer.h"
#include "World.h"
#include "Controller.h"

void Shell::onStart()
{
    this->tag = ETags::TShell;
    this->layer = LENEMY;
    this->startSprite = this->sprite;
    this->isActive = true;
    this->currentDir  = 1;
    this->speed = 120.0f;

    //top colider
    this->coliders.push_back({ ECol::Trigger, Vec2(2, -1), Vec2(this->sprite->w-4, 1) });
    //left colider
    this->coliders.push_back({ ECol::Trigger, Vec2(-1, 2), Vec2(1, this->sprite->h-4) });
    //right colider
    this->coliders.push_back({ ECol::Trigger, Vec2(this->sprite->w, 2), Vec2(1, this->sprite->h-4) });
}

void Shell::onUpdate()
{

    this->velocity.y +=  pow(world.gravity,2) * timer.deltaTime;
    this->velocity.x = (float)currentDir * (this->speed *  timer.deltaTime);

    this->pos.y +=  velocity.y * timer.deltaTime;
    this->checkCollisionY();
    
    if(this->isActive){
        this->sprite = this->startSprite + ANIMATION(0,4,100);
        this->pos.x +=  velocity.x;
    }
    if(this->checkCollisionX()){currentDir *= -1;}
}

bool Shell::onColide(Ent* ent,int colIndex)
{

    if(ent->tag == ETags::TController)
    {
        Controller* c = (Controller*)ent;
        if(c->godMode){return true;}
        if(colIndex == 1){
            c->velocity.y = -250;
            this->isActive =  !this->isActive;
            c->setImortal(0.5f);
        }
        else if(colIndex == 2 || colIndex == 3){
            c->takeDamage();
        }
    
        return true;
    }


    return true;
}

void Shell::onDead()
{

}

