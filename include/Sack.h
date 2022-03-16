#pragma once
#include "Ent.h"

enum ESackAnimation{
	ESack_None,
	ESack_Idle,
	ESack_Open
};


class Sack : public Ent {

public:
	Sack(Sprite* sprite)  : Ent(0,sprite,ECol::Trigger) {};
	void onStart();
	//void onRender();
    void onUpdate();
	bool onColide(Ent* ent,int colIndex);
    Ent* clone() { return new Sack(*this); }
private:
    Sprite* startSprite;
	bool colided = false;
	ESackAnimation currentAnimation = ESack_None;
	float timeNextAnimation = 0;
};
