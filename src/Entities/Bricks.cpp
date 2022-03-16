#include "Bricks.h"
#include "Controller.h"
#include "Particle.h"
#include "SoundManager.h"


void Brick::onStart()
{
     this->coliders.push_back({ ECol::Trigger, Vec2(4, sprite->h), Vec2(sprite->w-8,1) });
}

bool Brick::onColide(Ent* ent,int colIndex)
{
    if(ent->tag != ETags::TController){return true;}
    if(colIndex != 1){return true;} //colider index 1 is bottom colider

    //cast ent as controller
    Controller* controller = (Controller*)ent;
    if(controller->getSize() == ControllerSizes::CSMALL){return true;}

    controller->velocity.y = -60;
    //spawn particle
    Particle* p = new Particle(this->particleSprite, this->pos, Vec2(-75,-300), 1.0f, true);
    p->setAnimation(4,50);

    Particle* p2 = new Particle(*p);
    p->velocity = Vec2(75,-300);

    Particle* p3 = new Particle(*p);
    p->velocity = Vec2(75,-500);

    Particle* p4 = new Particle(*p);
    p->velocity = Vec2(-75,-500);

    particleSystem.addParticle(p);
    particleSystem.addParticle(p2);
    particleSystem.addParticle(p3);
    particleSystem.addParticle(p4);
    soundManager.playSFX("BrickShatter.wav");
    this->isAlive = false;

    return true;
} 