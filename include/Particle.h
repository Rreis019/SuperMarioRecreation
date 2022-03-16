#pragma once
#include "Ent.h"

class Particle : public Ent
{
    public:
        Particle(Sprite* spr,Vec2 position,Vec2 velocity,float lifeTime,bool gravity);
        void setAnimation(int animSpriteCount,int animDelay);
        Vec2  velocity = Vec2(0,0);
        float lifeTime = 0.0f;
        bool gravity = false;
        Particle* childParticle = nullptr; //child particle is added to world when main particle is destroyed 

        void onUpdate();
        Ent* clone(){ return new Particle(*this); }
    private:
        bool animation = false;
        int  animSpriteCount = 0;
        int  animDelay = 0;
        Sprite* startSprite;
};

class ParticleSystem : public Ent
{
    public:
        void addParticle(Particle* particle);
        void init();
    private:
};
extern std::vector<Sprite> particleSprites;

extern ParticleSystem particleSystem;