#pragma once
#include "Ent.h"
class Axe : public Ent {

public:
	Axe(Sprite* sprite)  : Ent(0,sprite,ECol::Trigger) {};
	void onStart();
	//void onRender();
    void onUpdate();
	bool onColide(Ent* ent,int colIndex);
    Ent* clone() { return new Axe(*this); }
private:
    Sprite* startSprite;
	bool colided = false;
};
