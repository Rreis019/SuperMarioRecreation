#pragma once
#include "LivingEnt.h"

class Toad : public LivingEnt {

public:
	Toad(Sprite* sprite)  : LivingEnt(0,sprite,ECol::Solid) {};
	void onStart();
	void onRender();
    void onUpdate();
	bool onColide(Ent* ent,int colIndex);
    Ent* clone() { return new Toad(*this); }
private:
    Sprite* startSprite;
	float jumpTime = 0.5f;
	float timeNextLetter = 0.0f;
	int numberOfLetters = 0;
	std::string finalText = "THANKS FOR PLAYING MY GAME";
	float waitToNextScreen = 0.5f;
};
