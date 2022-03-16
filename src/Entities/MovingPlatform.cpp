#include "MovingPlatform.h"
#include "World.h"
#include "Game.h"
#include "Timer.h"  

void MovingPlatform::onStart()
{
    this->sizeX = 3;
    this->coliders[0] = {ECol::Solid,Vec2(0,0),Vec2(sizeX * 16,8)};
}


void MovingPlatform::onUpdate()
{
    this->pos.x += this->velocity.x * timer.deltaTime;
    this->pos.y += this->velocity.y * timer.deltaTime;

    if(this->pos.y > game.height){
        this->pos.y = 0;
    }

    if(this->pos.y < -60){
        this->pos.y = game.height;
    }

}

bool MovingPlatform::onColide(Ent* ent,int colIndex)
{
    return true;
}


void MovingPlatform::onRender()
{
    Vec2 out = {0,0};
    if(world.currentCamera != NULL){
        if(world.currentCamera->W2S(this, out)){
            this->drawColiders(out);
            this->sprite->draw(out.x,out.y);
        }
    }
    else{ 
        out = this->pos;   this->drawColiders(out);
        this->sprite->draw(out.x,out.y);
    }    
    for(int i = 0; i < sizeX-1;i++){
        this->sprite->draw(out.x + (i+1) * 16, out.y);
    }
}

