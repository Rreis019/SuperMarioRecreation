#include "LivingEnt.h"
#include "World.h"

bool LivingEnt::checkCollisionX()
{
    if(noColision){return false;}
    bool result = false;
    for(int colIndex = 0;colIndex < this->coliders.size();colIndex++)
    {
        if(coliders[colIndex].type == ECol::Trigger){continue;}
        
        SDL_Rect myRect =  {
            (int)(pos.x + coliders[colIndex].offset.x),
            (int)(pos.y + coliders[colIndex].offset.y),
            (int)coliders[colIndex].size.x,
            (int)coliders[colIndex].size.y
        };

        for(int i = 0; i < world.getEntityCount(); i++)
        {
            Ent* ent = world.getEnt(i);

            if(ent == this){continue;}

            for(int col = 0; col < (int)ent->coliders.size();col++)
            {
                SDL_Rect rect = {
                    (int)(ent->pos.x + ent->coliders[col].offset.x),
                    (int)(ent->pos.y + ent->coliders[col].offset.y),
                    (int)ent->coliders[col].size.x,
                    (int)ent->coliders[col].size.y
                };

                if(SDL_HasIntersection(&myRect,&rect))
                {
                    bool doResolution = ent->onColide(this,col);

                    if(doResolution == false){continue;}

                    if(ent->coliders[col].type == ECol::Trigger){ continue;}

                    if(this->velocity.x > 0){ //moving right
                        this->pos.x = ent->pos.x - this->coliders[col].size.x;
                    }
                    else if(this->velocity.x < 0){ //moving left
                        this->pos.x = ent->pos.x + ent->coliders[col].size.x;
                    }
                    this->velocity.x = 0;
                    result = true;
                }
            }
        }
    }
    return result;
}

bool LivingEnt::checkCollisionY()
{
    if(noColision){return false;}
    bool result = false;
    for(int colIndex = 0;colIndex < this->coliders.size();colIndex++)
    {
        if(coliders[colIndex].type == ECol::Trigger){continue;}

        SDL_Rect myRect =  {
            (int)(pos.x + coliders[colIndex].offset.x),
            (int)(pos.y + coliders[colIndex].offset.y),
            (int)coliders[colIndex].size.x,
            (int)coliders[colIndex].size.y
        };

        for(int i = 0; i < world.getEntityCount(); i++)
        {
            Ent* ent = world.getEnt(i);

            //check if ent is a controller
            if(ent == this){continue;}

            for(int col = 0; col < (int)ent->coliders.size();col++)
            {
                SDL_Rect rect = {
                    (int)(ent->pos.x +  (int)ent->coliders[col].offset.x),
                    (int)(ent->pos.y +  (int)ent->coliders[col].offset.y),
                    (int)ent->coliders[col].size.x,
                    (int)ent->coliders[col].size.y
                };

                if(SDL_HasIntersection(&myRect,&rect))
                {
                    bool doResolution = ent->onColide(this,col);

                    if(doResolution == false){continue;}
                    if(ent->coliders[col].type == ECol::Trigger ){ continue;}


                    if(this->velocity.y > 0){ //moving down
                        this->pos.y = ent->pos.y - this->coliders[col].size.y;
                        isGrounded = true;
                    }
                    else if(this->velocity.y < 0){ //moving up
                        this->pos.y = ent->pos.y + ent->coliders[col].size.y +1;
                        isGrounded = false;
                    }
                    this->velocity.y = 0;
                    result = true;
                }
            }
        }
    }
    return result;
}
