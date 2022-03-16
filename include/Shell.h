#pragma once
#include "LivingEnt.h"

class Shell : public LivingEnt {

public:
    ~Shell(){}
	Shell(Sprite* sprite) : LivingEnt(0, sprite, ECol::Solid) {};
	//void onRender();
    void onStart();
    void onUpdate();
	bool onColide(Ent* ent,int colIndex);
    void onDead();
    Ent* clone() { return new Shell(*this); }
    bool isActive = true;
private:
    Sprite* startSprite;
    int currentDir = 1;
    float speed = 120.0f;
};
