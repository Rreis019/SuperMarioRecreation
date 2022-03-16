#include "Mushroom.h"
#include "Timer.h"
#include "World.h"
#include "Particle.h"
#include "Controller.h"
#include "SoundManager.h"

 void Mushroom::onStart()
 {
     this->velocity = Vec2(0,0);
     this->layer = ELayers::LPowerUp;
     this->coliders.push_back({ ECol::Trigger, Vec2(-2, -2), Vec2(sprite->w+4,sprite->h+4) });

 }

void Mushroom::onUpdate()
{
    this->velocity.y +=  pow(world.gravity,2) * timer.deltaTime;
    this->velocity.x = currentDir * (this->speed *  timer.deltaTime);

    
    this->pos.x +=  velocity.x;
    if(this->checkCollisionX()){currentDir *= -1;}

    this->pos.y +=  velocity.y * timer.deltaTime;
    this->checkCollisionY();
}

bool Mushroom::onColide(Ent* ent,int colIndex)
{
    if(ent->tag == ETags::TController)
    {
        this->isAlive = false;
        Particle* UP1 = new Particle(&particleSprites[8],this->pos,Vec2(0,-30),0.4f,false);
        particleSystem.addParticle(UP1);
        //cast ent as conttroller
        Controller* controller = (Controller*)ent;

        if(controller->getSize() == CSMALL){
            controller->changeSize(CMEDIUM);
        }

        soundManager.playSFX("PowerUp.wav");

        return false;
    }
    return true;
}
    