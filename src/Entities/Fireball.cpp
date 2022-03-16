#include "Fireball.h"
#include "Game.h"
#include "Timer.h"
#include "World.h"
#include "Particle.h"

void Fireball::onStart()
{
	this->tag = TFireball;
	this->startSprite = this->sprite;
}
//void onRender();

void Fireball::onUpdate()
{
	this->sprite = this->startSprite + ANIMATION(0,8,100);

	this->velocity.y +=  pow(world.gravity,2) * timer.deltaTime;


	if(this->pos.y > game.height){
		this->isAlive = false;
	}



	this->pos.y += velocity.y * timer.deltaTime;
	if (this->checkCollisionY() || this->pos.y > game.height)
	{
		if(isGrounded == false){
			this->velocity.y = abs(this->velocity.y);
		}
		else{
			this->velocity.y = -350;
		}
	}

	this->pos.x +=  direction * 180 * timer.deltaTime;
	if (this->checkCollisionX())
	{
		Ent temp = *this;
		this->tag = ETags::TEnt;
		this->onColide(&temp,0);
	}

}

bool Fireball::onColide(Ent* ent,int colIndex)
{
	if(ent->tag == TController || ent->tag == TFireball){return false;}


	Particle* explosion = new Particle(&particleSprites[22],this->pos,Vec2(0,0),0.3f,false);
	explosion->setAnimation(3,100);
	particleSystem.addParticle(explosion); 
	this->isAlive = false;



	if(ent->layer = LENEMY){return false;}
	return true;
}