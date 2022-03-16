#pragma once
#include "Ent.h"

//InvisibleBlock is responsible to limit enemies moving outside the screen
class InvisibleBlock : public Ent {

public:
	InvisibleBlock(Sprite* sprite)  : Ent(0,sprite,ECol::Solid) {};
	bool onColide(Ent* ent,int colIndex);
    Ent* clone() { return new InvisibleBlock(*this); }

private:
};