#pragma once
#include "Vec2.h"
#include "Sprite.h"
#include <vector>

enum ETags{
    TEnt = 0,
    TController,
    TShell,
    TBowser,
    TFireball,
    TToad,
    TSack
};


enum ECol{
    Trigger,
    Solid
};

enum ELayers
{
    LNONE = 0,
    LFIREBALCHAIN = 1,
    LPLAYER,
    LTUBE,
    LENEMY,
    LPowerUp,
};



struct Colider{
    ECol type;
    Vec2 offset; //relative to the ent
    Vec2 size;
};



class Ent
{
    public: 

    	//Entity position
        Vec2 pos = Vec2(0,0); 

        //Identifies the object's class
        unsigned short tag = ETags::TEnt; 

        //Layer determines whether to draw over an object or not
        unsigned short layer = 0; 	

        //Identify if the Ent is dead or alive
        bool isAlive = true; 

        SDL_RendererFlip flip = SDL_FLIP_NONE;

        //Colliders for the Ent
        std::vector<Colider> coliders = std::vector<Colider>();

        Sprite* sprite;

        virtual ~Ent(){  }
        Ent() {};
        Ent(float x,float y) : pos(x,y) {};
        Ent(Vec2 pos, int tag, int layer, Sprite* sprite);
        Ent(int layer,Sprite* sprite,ECol ecol);
        Ent(int layer,Sprite* sprite){this->layer  = layer; this->sprite = sprite;}

        void drawColiders(Vec2 out);
        virtual void onStart() {};
        virtual void onUpdate() {};
        virtual void onRender();
	    virtual void onDead() {};
	    virtual bool onColide(Ent* ent,int colIndex) { return true;} //return true if u want resolution
        virtual Ent* clone(); //PROTOTYPE DESIGN PATTERN
};

