#include "Bowser.h"
#include "Timer.h"
#include "World.h"
#include "Prefabs.h"
#include "FireballBowser.h"
#include "Controller.h"
#include "Particle.h"
#include "Hud.h"
#include "Logger.h"


#define FIREBALL_DELAY 1.5f
#define TAKE_DAMAGE_DELAY 0.4f

void Bowser::onStart()
{
    this->startPos = this->pos;
    this->dirX = -1;
    this->flip = SDL_FLIP_HORIZONTAL;
    this->tag = ETags::TBowser;
    this->startSprite = this->sprite;
}
void Bowser::onUpdate()
{

    if(currentAnimation == EBOWSER_IDLE){
        this->sprite = this->startSprite + ANIMATION(0,3,200);
    }
    else if(currentAnimation == ETAKINGDAMAGE){
        this->sprite = this->startSprite + ANIMATION(5,2,100);
        takeDamageTime -= timer.deltaTime;
        if(takeDamageTime <= 0){
            currentAnimation = EBOWSER_IDLE;
        }
    }
    else if(currentAnimation == EATTACKING){
        this->sprite  = this->startSprite + 3;
        openMouthTime -= timer.deltaTime;
        if(openMouthTime <= 0){
            this->sprite = this->startSprite + 4;
            closeMouthTime -= timer.deltaTime;
            if(sendFireball == false){
                sendFireball = true;
                FireballBowser* fireball = new FireballBowser(&effectsSprites[8],dirX);
                fireball->pos = this->pos;
                fireball->pos.y += 8;
                fireball->pos.x -= 8;
                world.addEntity(fireball);
            }


            if(closeMouthTime <= 0){
                currentAnimation = EBOWSER_IDLE;
                sendFireball = false;
            }
        }
    }



    this->velocity.y +=  pow(world.gravity*0.5f,2) * timer.deltaTime;

    this->velocity.x = dirX * (30.0f * timer.deltaTime);

    this->pos.x += velocity.x;
    this->checkCollisionX();

    this->pos.y +=  velocity.y * timer.deltaTime;
    if(checkCollisionY())
    {
        if(!this->isGrounded) {return;}

        dirX = rand() % 2;
        if (dirX == 0){dirX = -1;}

        if (this->pos.x < (startPos.x - Limit))
        {
            dirX = 1;
        }
        else if (this->pos.x + this->sprite->w >= startPos.x)
        {
            dirX = -1;
        }
        this->velocity.y = -180;
    }

    fireballTime -= timer.deltaTime;

    if(fireballTime <= 0)
    {
        fireballTime = FIREBALL_DELAY;
        currentAnimation = EATTACKING;
        openMouthTime = 0.4f;
        closeMouthTime = 0.3f;
        log("Fireball created\n");
    }
    
}


bool Bowser::onColide(Ent* ent,int colIndex)
{
    if(ent->tag == ETags::TController){
        //cast to controller
        Controller* controller = (Controller*)ent;
        controller->takeDamage();
    }

    if(ent->tag == ETags::TFireball && this->currentAnimation != ETAKINGDAMAGE)
    {
        this->health--;
        this->currentAnimation = ETAKINGDAMAGE;
        this->takeDamageTime = TAKE_DAMAGE_DELAY;
        if(this->health <= 0)
        {
            this->onDead();
        }
    }
    return false;
}

void Bowser::onDead()
{
    this->isAlive = false;
    particleSystem.addParticle(new Particle(&particleSprites[6],this->pos, Vec2(0,-30), 0.5f, false));
    Particle* goomba = new Particle(&enemySprites[0],Vec2(pos.x + sprite->w/2,pos.y + sprite->h/2), Vec2(0,0), 1.5f, true);
    goomba->flip = SDL_FLIP_VERTICAL;
    particleSystem.addParticle(goomba);
    hud.addScore(4000);
}