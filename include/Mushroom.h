#pragma once
#include "LivingEnt.h"
class Mushroom : public LivingEnt {

public:

	Mushroom(Sprite* sprite)  : LivingEnt(0,sprite,ECol::Solid) {
		this->velocity = Vec2(0,0);
	};
	void onStart();
	//void onRender();
    void onUpdate();
	bool onColide(Ent* ent,int colIndex);
    Ent* clone() { return new Mushroom(*this); }
	int currentDir = 1;
	float speed = 60;

private:
};
