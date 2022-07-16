#include "Teleport.h"
#include "World.h"
#include "Input.h"
#include "Game.h"
#include "Controller.h"
#include "Timer.h"
#include "SoundManager.h"

void Teleport::changeScene()
{

    Controller* controller = (Controller*)player;
    controller->gravity = true;
    controller->noColision = false;
    controller->isFreeze = false;
    controller->jumpStartTime =0;
    

    //loop thorought all controllers and teleport to dest pos
    for(int i= 0 ; i < world.controllers.size(); i++)
    {
        world.controllers[i]->pos = this->destPos;
        Controller* controller = (Controller*)world.controllers[i];
        controller->centerCamera();
    }
    SDL_Delay(100);
    world.changeScene(this->nextScene);

}

Teleport::Teleport(Vec2 pos,int changeScene,Vec2 destPos,int dir)
{
    this->pos = pos;
    this->nextScene = changeScene;
    this->destPos = destPos;
    this->dir = dir;
}

void Teleport::onStart()
{
    this->coliders.push_back(Colider{ECol::Trigger,Vec2(0,0),Vec2(4,8)});
}

void Teleport::onRender()
{
    if(world.currentCamera != NULL){
        Vec2 out = {0,0};
        if(world.currentCamera->W2S(this->pos, &out)){
        
             this->drawColiders(out);}
    }
    else{  
        this->drawColiders(pos);
    }    
}


void Teleport::onUpdate()
{
    if(!canTeleport){return;}

    Controller* controller = (Controller*)player;

    controller->gravity = false;
    controller->noColision = true;
    switch(dir){
        case UP:

            break;
        case DOWN:
        {
            if(player->pos.y > this->pos.y + 8+5){
                canTeleport = false;
                changeScene();
            }
            else{
                controller->changeSprite(12);
                player->pos.y +=  30 * timer.deltaTime;
            }
            break;
        }
        case RIGHT:
        {
            if (player->pos.x > this->pos.x + 8 + 16){
                canTeleport = false;
                changeScene();
            }
            else{
                //cast ent to controller
                controller->moveRight();
            }
            break;
        }
    }
}

bool Teleport::onColide(Ent* ent,int colIndex)
{
    if(ent->tag != ETags::TController){return true;}
    if(canTeleport){return true;}
    //cast as controller
    Controller* controller = (Controller*)ent;

    switch(dir)
    {
        case UP:
            isKeyDown(controller->controls->jump) ? canTeleport = true : canTeleport = false;
            break;
        case LEFT:
            isKeyDown(controller->controls->left) ? canTeleport = true : canTeleport = false;
            break;
        case DOWN:
            if(isKeyDown(controller->controls->down))
            {
                canTeleport = true;
                controller->pos.x = this->pos.x  + this->coliders[0].size.x/2 - controller->coliders[0].size.x/2;
            } 
            else{
                canTeleport = false;
            }
            break;
        case RIGHT:
            if(isKeyDown(controller->controls->right)){
                canTeleport = true;
                //if player is in the air and is pressing right, teleport him to same y pos as teleport
                controller->pos.y = this->pos.y + this->coliders[0].size.y - controller->coliders[0].size.y;
                controller->changeSprite(0);
            }
            else{
                canTeleport = false;
            } 

            break;
    }

    if(canTeleport){
        player = ent;
        controller->freeze();
        soundManager.playSFX("Warp.wav");
    }

    return true;
}
