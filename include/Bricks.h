#pragma once
#include "Ent.h"

class Brick : public Ent {

public:

	Brick(Sprite* sprite,Sprite* partprite)  : Ent(0,sprite,ECol::Solid) { this->particleSprite = partprite; }
    void onStart();
	//void onRender();
    //void onUpdate();
	bool onColide(Ent* ent,int colIndex);
    Ent* clone() { return new Brick(*this); }

private:
    Sprite* particleSprite;
};
