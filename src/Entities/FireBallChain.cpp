#include "FireBallChain.h"
#include "World.h"
#include "Prefabs.h"
#include "Timer.h"
#include "Controller.h"

#define chainDistance 10

void FireBallChain::onStart()
{
    this->chainLength = 5;

    for(int i = 0;i < chainLength;i++)
    {
        this->coliders.push_back({ ECol::Trigger, Vec2((i*chainDistance) * -1 + 4, 4), Vec2(8,8)});
    }


}

void FireBallChain::onRender()
{
    Vec2 out = {0,0};
    bool canRender = true;
    if(world.currentCamera != NULL){
         canRender = world.currentCamera->W2S(this, out);
    }
    else{ out = this->pos; }    

    
    if(canRender) {    this->sprite->draw(out.x,out.y,flip);}
    this->drawColiders(out);

    for(int i = 0; i < chainLength; i++){
        effectsSprites[ANIMATION(0,8,200)].draw(
            out.x+this->coliders[i+1].offset.x,
            out.y+this->coliders[i+1].offset.y,
            flip);
    }



}

void FireBallChain::onUpdate()
{
    chainAngle += 160*timer.deltaTime;

    for(int i = 0; i < chainLength; i++){
        Vec2 relative = Vec2(0,0);
        relative.forward(chainAngle);
        relative *= i * chainDistance;
        relative.x += 4;
        relative.y += 4;
        this->coliders[i+1].offset = relative;
    }
}

bool FireBallChain::onColide(Ent* ent,int colIndex)
{
    if(colIndex == 0 || colIndex == 1){return true;} //0 = self block solid, 1 = center fireball inside solid

    if(ent->tag == ETags::TController){
        //cast as controller
        Controller* controller = (Controller*)ent;
        controller->takeDamage();
    }


    return true;
}
