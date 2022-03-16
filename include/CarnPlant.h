#pragma once
#include "Ent.h"

class CarnPlant : public Ent {

public:
    ~CarnPlant(){}
	CarnPlant(Sprite* sprite) : Ent(0, sprite, ECol::Trigger) {};
    void onStart();
    void onUpdate();
	bool onColide(Ent* ent,int colIndex);
    Ent* clone() { return new CarnPlant(*this); }

private:
    Sprite* startSprite;
    float startY = 0;
    float velY = 30.0f;
    float waitTime = 0;
    bool  inofensive = false;
};
