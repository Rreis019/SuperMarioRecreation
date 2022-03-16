#include "MysteryBox.h"
#include "LivingEnt.h"
#include "Timer.h"
#include "Utils.h"
#include "Hud.h"
#include "Particle.h"
#include "Prefabs.h"
#include "World.h"
#include "SoundManager.h"

#define SHAKE_DURATION 0.05f

void MysteryBox::onStart()
{
    this->coliders.push_back({ ECol::Trigger, Vec2(4, sprite->h), Vec2(sprite->w-8,1) });
    this->startSprite = sprite;
    this->startY = pos.y;
}

void MysteryBox::onUpdate()
{
    if(!this->isEmpty){
        this->sprite = this->startSprite + ANIMATION(0,3,300);
    }
}

void MysteryBox::onRender()
{
     Vec2 out = {0,0};
     bool canRender = true;
    if(world.currentCamera != NULL){
       canRender = world.currentCamera->W2S(this, out);
    }
    else{ 
        out = this->pos;
    }

    if(!canRender){return;}
    
    this->drawColiders(out);
    Vec2 drawPos = {out.x,out.y};

    if(shakeUp)
    {
        this->elapsedTime+= timer.deltaTime;
        float percentage = elapsedTime / SHAKE_DURATION;
        drawPos.y = lerp(startY,startY-4, percentage);

        if(percentage >= 1.0f){
            shakeUp = false;
            shakeDown = true;
            elapsedTime = 0.0f;
        }

    }

    if(shakeDown){
        this->elapsedTime+= timer.deltaTime;
        float percentage = elapsedTime / SHAKE_DURATION;
        drawPos.y = lerp(startY-4,startY, percentage);

        if(percentage >= 1.0f){
            shakeDown = false;
            shakeUp = false;
            elapsedTime = 0.0f;
        }
    }

    this->sprite->draw(drawPos.x,drawPos.y,flip);
}


bool MysteryBox::onColide(Ent* ent,int colIndex)
{
    if(this->isEmpty){return true;}
    if(ent->tag != ETags::TController){return true;}
    if(colIndex != 1){return true;} //colider index 1 is bottom colider

    switch (holdItem)
    {
        case EHoldCoin:
        {

            hud.addScore(200);
            
            Particle* score200 = new Particle(&particleSprites[1],this->pos, Vec2(0,-30), 0.5f, false);
            Particle* explosionCoin = new Particle(&particleSprites[17], Vec2(0,0), Vec2(0,-300), 0.1f, true);
            Particle* coinParticle = new Particle(&particleSprites[13], Vec2(pos.x-2,pos.y-6), Vec2(0,-100), 0.5f, false);
            
            explosionCoin->childParticle = score200;
            explosionCoin->setAnimation(4,50);
            coinParticle->setAnimation(4,100);
            coinParticle->childParticle = explosionCoin;
            particleSystem.addParticle(coinParticle);
            hud.addCoin(1);

            break;
        }
        case EHoldMushroom:
        {
            world.addEntity(getPrefab(28,pos.x,pos.y - 25),world.getScene());    
            soundManager.playSFX("ItemSprout.wav");
            break; 
        }
        case EHoldFlower:
        {
            world.addEntity(getPrefab(29,pos.x,pos.y - 16),world.getScene());
            break; 
        }
        case EHoldStar:
        {
            world.addEntity(getPrefab(16,pos.x,pos.y - 16),world.getScene());
            break; 
        }
    }

    isEmpty = true;
    shakeUp = true;
    this->sprite = this->startSprite+4;
    return true;
}