#include "Flower.h"
#include "Controller.h"
#include "Particle.h"
#include "Hud.h"

void Flower::onStart()
{
    this->coliders[0].type = ECol::Trigger;
}

bool Flower::onColide(Ent* ent,int colIndex)
{
    if(ent->tag != ETags::TController){return true;}
    this->isAlive = false;
    Controller* controller = (Controller*)ent;
    controller->changeSize(ControllerSizes::CFIRE);
    particleSystem.addParticle(new Particle(&particleSprites[4],this->pos, Vec2(0,-30), 0.5f, false));
    hud.addScore(1000);
    return true;
}