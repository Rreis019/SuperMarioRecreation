#include "Axe.h"
#include "Timer.h"
#include "World.h"

void Axe::onStart()
{
    this->startSprite = this->sprite;
    this->colided = false;
}

//void onRender();
void Axe::onUpdate()
{
    if(colided){return;}



    this->sprite = this->startSprite + ANIMATION(0,3,50);
}
bool Axe::onColide(Ent* ent,int colIndex)
{
    if(ent->tag != ETags::TController){return false;}
    if(colided){return false;}
    colided = true;
    //delete all bowsers
    for(int i = 0 ; i < world.getEntityCount();i++){
        Ent* ent = world.getEnt(i);
        if(ent->tag == ETags::TBowser){
            ent->onDead();
        }
    }
    this->sprite = startSprite;
    return false;
}
