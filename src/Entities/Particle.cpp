#include "Particle.h"
#include "Timer.h"
#include "World.h"

ParticleSystem particleSystem = ParticleSystem();
std::vector<Sprite> particleSprites;

Particle::Particle(Sprite* spr,Vec2 position,Vec2 velocity,float lifeTime,bool gravity)
{
    this->sprite = spr;
    this->pos = position;
    this->velocity = velocity;
    this->lifeTime = lifeTime;
    this->gravity = gravity;
    this->startSprite = spr;
}

void Particle::onUpdate()
{
    if(lifeTime < 0.0f){
        if(this->childParticle != nullptr){
            childParticle->pos = this->pos;
            particleSystem.addParticle(this->childParticle);
        }
        this->isAlive = false;
    }
    
    if(this->animation){
        this->sprite = startSprite + ANIMATION(0, animSpriteCount, animDelay);
    }

    if(this->gravity){
        this->velocity.y +=  pow(world.gravity,2) *  timer.deltaTime;
    }

    this->pos.x += velocity.x *  timer.deltaTime;
    this->pos.y += velocity.y *  timer.deltaTime;
    lifeTime -=   timer.deltaTime;
}

void Particle::setAnimation(int animSpriteCount,int animDelay)
{
    this->animation = true;
    this->animSpriteCount = animSpriteCount;
    this->animDelay = animDelay;
}

void ParticleSystem::init()
{
    loadMultipleImages(particleSprites,"Resources/Popups/","popup_");
}

void ParticleSystem::addParticle(Particle* particle)
{
    world.addEntity(particle,world.getScene());
}