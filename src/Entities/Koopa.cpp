#include "Koopa.h"
#include "Timer.h"
#include "World.h"
#include "Controller.h"
#include "Particle.h"
#include "Hud.h"
#include "Game.h"
#include "Shell.h"

void Koopa::onStart()
{
    this->layer = ELayers::LENEMY;
    this->startSprite = this->sprite;
    this->coliders.push_back({ ECol::Trigger, Vec2(2, -2), Vec2(16-4, 1) }); //topcolider
    this->coliders.push_back({ ECol::Trigger, Vec2(-1, 4), Vec2(1, 24-8) }); 
    this->coliders.push_back({ ECol::Trigger, Vec2(16, 4), Vec2(1, 24-8) });
    this->currentDir = 1;
}

void Koopa::onUpdate()
{
    if(this->deadAnimation){this->onDead();}

    if(this->pos.y > game.height + 100){this->isAlive = false;}

    this->velocity.y +=  pow(world.gravity,2) * timer.deltaTime;

    if(!this->isFreeze){
        this->flip = currentDir == 1 ? SDL_FLIP_NONE : SDL_FLIP_HORIZONTAL;
        this->velocity.x = currentDir * (this->speed *  timer.deltaTime);
    }    
    
    if(!noAnimation) {this->sprite = startSprite + ANIMATION(0, 2, 200);}
    this->pos.x +=  velocity.x;
    if(this->checkCollisionX()){currentDir *= -1;}

    this->pos.y +=  velocity.y * timer.deltaTime;
    this->checkCollisionY();
}

bool Koopa::onColide(Ent* ent,int colIndex)
{
    
    if(ent->tag == ETags::TShell || ent->tag == ETags::TFireball){

        
        if(ent->tag == ETags::TShell) {
            Shell* s  = (Shell*)ent;
            if(s->isActive == false){return true;}
        }

        this->speed = 0; //dont move horizontally
        this->velocity.x = 0;
        this->velocity.y = -500;
        this->delayToDie = 1000;
        this->isFreeze = true;
        this->coliders.clear();
        this->sprite = startSprite;
        this->flip = SDL_FLIP_VERTICAL;

        if(ent->tag == ETags::TFireball){
            ent->isAlive = false;
            ent->onColide(this,0);
            particleSystem.addParticle(new Particle(&particleSprites[0],this->pos, Vec2(0,-30), 0.5f, false));
            hud.addScore(100);
        }

    }


    if(ent->tag != ETags::TController){return true;}
    Controller* c = (Controller*)ent;
    if(colided ){return true;}
    if(colIndex == 1)
    {
        if(c->godMode){return true;}

        LivingEnt* le = (LivingEnt*)ent;
        le->velocity.y = -450;
        particleSystem.addParticle(new Particle(&particleSprites[0],this->pos, Vec2(0,-30), 0.5f, false));
        hud.addScore(100);
        c->setImortal(0.5f);

        Shell * shell = new Shell(shellSprite);
        shell->pos = this->pos;
        shell->pos.y += 8;
        world.addEntity(shell,world.getScene());//spawn shell
        this->isAlive = false;
        this->colided = true;
    }
    else if(colIndex == 2 || colIndex == 3){
        c->takeDamage();
    }
    return true;
}

void Koopa::onDead()
{
    if(timer.startTick > deadTime + 200)
    {
        this->isAlive = false;
    }
}