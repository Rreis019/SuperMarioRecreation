#pragma once
#include "Ent.h"

class Coin : public Ent {

public:

	Coin(Sprite* sprite)  : Ent(0,sprite,ECol::Trigger) {};
	//void onRender();
	void onStart();
    void onUpdate();
	bool onColide(Ent* ent,int colIndex);
    Ent* clone() { return new Coin(*this); }

private:
	Sprite* startSprite;
};
