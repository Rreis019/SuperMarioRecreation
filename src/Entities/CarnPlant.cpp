#include "CarnPlant.h"
#include "Timer.h"
#include "Particle.h"
#include "Hud.h"
#include "Controller.h"

#define WaitDelay 2.0f

void CarnPlant::onStart()
{
    this->pos.x -= 8;
    this->pos.y += (32 -  this->sprite->h);
    this->startY = this->pos.y;
    this->inofensive = true;
    this->waitTime = 0;
    this->startSprite = this->sprite;
}

void CarnPlant::onUpdate()
{

    this->sprite = startSprite + ANIMATION(0, 2, 200);
    
    if (this->waitTime > 0)
    {
        this->waitTime -= timer.deltaTime;
        return;
    }


    if(this->pos.y >= this->startY-1 && this->pos.y <= (startY + sprite->h+1))
    {
        this->inofensive = false;
    }
    else
    {
        this->inofensive = true;
    }

    if (this->pos.y > startY + sprite->h + 2)
	{
		velY *= -1;
        waitTime  = WaitDelay;
        this->pos.y = startY + sprite->h + 2;
	}
    else if (this->pos.y  <= startY)
	{
		velY *= -1;
        waitTime  = WaitDelay;
        this->pos.y = startY;
	}

    this->pos.y += this->velY * timer.deltaTime;

    /*
    this->pos.y >= startY + sprite->h ? this->inofensive = true : this->inofensive = false;

	else if (this->pos.y  < startY)
	{
		velY *= -1;
        waitTime  = WaitDelay;
	}
*/
}

bool CarnPlant::onColide(Ent* ent,int colIndex)
{
    if(ent->tag == TFireball){
        particleSystem.addParticle(new Particle(&particleSprites[1],this->pos, Vec2(0,-30), 0.5f, false));
        hud.addScore(200);
        this->isAlive = false;
    }

    if(inofensive){return true;}
    if(ent->tag == ETags::TController){
        Controller* c = (Controller*)ent;
        c->takeDamage();
    }

    return true;
}

