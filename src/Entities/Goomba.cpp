#include "Goomba.h"
#include "Timer.h"
#include "World.h"
#include "Controller.h"
#include "Particle.h"
#include "Hud.h"
#include "Game.h"
#include "SoundManager.h"
#include "Logger.h"
#include "Shell.h"

void Goomba::onStart()
{
    startSprite = sprite;   
    this->coliders.push_back({ ECol::Trigger, Vec2(2, -2), Vec2(16-4, 1) }); //topcolider

    this->coliders.push_back({ ECol::Trigger, Vec2(-1, 2), Vec2(1, 16-4) }); 
    this->coliders.push_back({ ECol::Trigger, Vec2(16, 2), Vec2(1, 16-4) });
    this->layer = ELayers::LENEMY;
    this->isFreeze = false;
    this->noColision = false;
}

void Goomba::onUpdate()
{
    
    if(this->deadAnimation){this->onDead();}

    if(this->pos.y > game.height + 100){this->isAlive = false;log("Goomba dead\n");}

    if(this->isFreeze){return;}

    if(!noAnimation) {this->sprite = startSprite + ANIMATION(0, 2, 200);}
    this->velocity.y +=  pow(world.gravity,2) * timer.deltaTime;


    this->velocity.x = currentDir * (this->speed *  timer.deltaTime);

    this->pos.y +=  velocity.y * timer.deltaTime;
    this->checkCollisionY();
    
    this->pos.x +=  velocity.x;
    if(this->checkCollisionX()){currentDir *= -1;}

}

bool Goomba::onColide(Ent* ent,int colIndex)
{
    if(ent->tag == ETags::TShell || ent->tag == ETags::TFireball){


        if(ent->tag == ETags::TShell) {
            Shell* s  = (Shell*)ent;
            if(s->isActive == false){return true;}
        }


        this->sprite = startSprite + 2;
        this->deadAnimation = true;
        this->deadTime = timer.startTick;
        this->isFreeze = false;
        this->currentDir = 0; //dont move horizontally
        this->velocity.x = 0;
        this->velocity.y = -500;
        this->delayToDie = 1000;
        this->noAnimation = true;
        this->sprite = startSprite;
        this->flip = SDL_FLIP_VERTICAL;

        this->coliders.clear();
        if(ent->tag == ETags::TFireball){
            ent->onColide(this,0);
            particleSystem.addParticle(new Particle(&particleSprites[0],this->pos, Vec2(0,-30), 0.5f, false));
            hud.addScore(100);
        }
        return false;
    }



    if(ent->tag != ETags::TController){return true;}
    Controller* c = (Controller*)ent;
    if(colIndex == 1){ //When goomba is dying
        if(c->godMode){return true;} //if the player is in godmode, dont kill him
        soundManager.playSFX("Stomp.wav",0);
        this->sprite = startSprite + 2;
        this->deadAnimation = true;
        this->deadTime = timer.startTick;
        this->isFreeze = true;
        this->coliders.clear();
        this->delayToDie = 200;
        LivingEnt* le = (LivingEnt*)ent;
        le->velocity.y = -250;
        particleSystem.addParticle(new Particle(&particleSprites[0],this->pos, Vec2(0,-30), 0.5f, false));
        hud.addScore(100);
    }
    else if(colIndex == 2 || colIndex == 3){ //When player get hit by goomba
        c->takeDamage();
        this->currentDir *= -1;
    }

    return true;
}

void Goomba::onDead()
{
    if(timer.startTick > deadTime + delayToDie)
    {
        this->isAlive = false;
        
    }
}