#include "Flag.h"
#include "World.h"
#include "Controller.h"
#include "Timer.h"
#include "LevelManager.h"
#include "Game.h"
#include "ScreenManager.h"
#include "SaveSystem.h"
#include "Hud.h"
#include "Particle.h"
#include "SoundManager.h"
#include "Logger.h"

void Flag::onStart()
{
    this->sizeY = 9;
    for(int i = 0;i < sizeY;i++)
    {
        coliders.push_back({ ECol::Trigger, Vec2(7, (i+1)*sprite->h), Vec2(2, sprite->h) });
    }
    flagY = 0;
    playersOnFlag = nullptr;
}


void Flag::onRender()
{
    Vec2 out = {0,0};
    Sprite* mastro = sprite+1;
    Sprite* flagS = sprite+2;
    if(world.currentCamera != NULL){
        if(world.currentCamera->W2S(this, out)){
            this->drawColiders(out);
            this->sprite->draw(out.x,out.y);
        }
    }
    else{ 
        out = this->pos;   this->drawColiders(out);
        this->sprite->draw(out.x,out.y);
    }    
    
    flagS->draw(out.x+8,out.y+16+flagY);
    for(int i =0 ; i< sizeY;i++){mastro->draw(out.x, out.y + (i+1)*mastro->h);}
}


void Flag::onUpdate()
{
    if(playersOnFlag == nullptr){return;}
    Controller* controller = (Controller*)playersOnFlag;

    if(isPlayerFlagDown)
    {
        //player go down flag
        playersOnFlag->pos.y += 60 * timer.deltaTime;
        flagY += 60 * timer.deltaTime;

        float lastY = (this->pos.y + (sizeY+1)*sprite->h) - playersOnFlag->coliders[0].size.y;
        bool canLeave = true;

        if(playersOnFlag->pos.y > lastY) 
        {
            playersOnFlag->pos.y = lastY;
            controller->changeSprite(8);
        }
        else{
            canLeave = false;
            controller->changeSprite(ANIMATION(8,2,400));
        }


        flagY > (sizeY-1)*sprite->h ? flagY = (sizeY-1)*sprite->h : canLeave = false;

        if(canLeave){
            controller->currentDir = 1;
            controller->pos.x += 16;
            controller->pos.y -= 4;
            controller->changeSprite(8);
            isPlayerFlagDown = false;
            timeFlagDown = timer.startTick;
        }
    }
    else if(nextLevel == false)
    {
        if(removeHook == false)
        {
            if(timer.startTick > timeFlagDown + 400)
            {
                controller->currentDir = 0;
                controller->pos.x += 8;
                controller->changeSprite(1);
                controller->gravity = true;
                controller->noColision = false;
                controller->isJumping = false;
                removeHook = true;
            }

        }
        else{
            if(controller->pos.x > levelManager.finalPos.x)
            {
                controller->pos.x = levelManager.finalPos.x;
                controller->centerCamera();
                controller->changeSprite(12);
                nextLevel = true;
                nextTime = timer.startTick;
            }
            else{
                controller->moveRight();
            }
        }
    }
    else{
        controller->velocity.x = 0;
        if(timer.startTick > nextTime + 3000)
        {
            levelManager.currentLevel+= 1;
            SaveData data =  {levelManager.currentLevel,hud.getScore(),hud.lifes,hud.getCoin()};
            saveSystem.save(saveSystem.currentSaveSlot,data);
            screenManager.changeScreen(NEXT_LEVEL_SCREEN);
            
        }
    }
}

bool Flag::onColide(Ent* ent,int colIndex)
{
    if(ent->tag != ETags::TController){return true;}
    if(isPlayerFlagDown){return true;}


    //cast ent as Controller
    Controller* c = (Controller*)ent;

    //freeze the player
    c->freeze();
    c->changeSprite(8);
    c->pos.x = this->pos.x-8;
    c->noColision = true;
    c->gravity = false;
    c->velocity.y = 0;
    c->velocity.x = 0;
    isPlayerFlagDown = true;
    playersOnFlag = ent;
    soundManager.playMusic("11.course Clear.mp3",1);
    
    int extraPoints [] = {4000,4000,4000,2000,2000,800,800,400,400,100};
    int particleIndex [] = {6,6,6,5,5,3,3,2,2,0};
    Particle* p = new Particle(&particleSprites[particleIndex[colIndex]],Vec2(this->pos.x+20,this->pos.y+90),Vec2(0,-30),2.0f,false);
    particleSystem.addParticle(p);
    hud.addScore(extraPoints[colIndex]);
    log("extrapoints %d",extraPoints[colIndex]);
    return true;
}