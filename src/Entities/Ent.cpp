#include "Ent.h"
#include "Drawings.h"
#include "Game.h"
#include "World.h"

//Draw colidders
//#define DRAW_DEBUG


Ent::Ent(Vec2 pos, int tag, int layer, Sprite* sprite)
{
    this->pos = pos;
    this->tag = tag;
    this->layer = layer;
    this->sprite = sprite;
}

void Ent::onRender(){

    Vec2 out = {0,0};
    if(world.currentCamera != NULL){
        if(world.currentCamera->W2S(this, out)){
            this->drawColiders(out);
            this->sprite->draw(out.x,out.y,flip);
        }
    }
    else{ 
        out = this->pos;   this->drawColiders(out);
        this->sprite->draw(out.x,out.y,flip);
    }    


}

Ent::Ent(int layer,Sprite* sprite,ECol ecol)
{
    this->layer = layer;
    this->sprite = sprite;
    this->coliders.push_back({ ecol, Vec2(0, 0), Vec2(sprite->w, sprite->h) });
}

void Ent::drawColiders(Vec2 out)
{
    #ifndef DRAW_DEBUG
        return;
    #endif

    for (int i = 0; i < (int)coliders.size(); i++)
    {
        //drawFilledRect(SDL_Renderer* renderer ,int x,int y,int w,int h, SDL_Color color)
        drawRect(renderer,
        coliders[i].offset.x + out.x,
        coliders[i].offset.y + out.y,
        coliders[i].size.x,
        coliders[i].size.y,1,
        {coliders[i].type*255,0,0,255});
    }
}
 



Ent* Ent::clone()
{
    return new Ent(*this);
}