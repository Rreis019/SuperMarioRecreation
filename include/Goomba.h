#pragma once
#include "LivingEnt.h"

class Goomba : public LivingEnt {

public:
    ~Goomba(){}
	Goomba(Sprite* sprite) : LivingEnt(0, sprite, ECol::Solid) {};
	//void onRender();
    void onStart();
    void onUpdate();
	bool onColide(Ent* ent,int colIndex);
    void onDead();
    Ent* clone() { return new Goomba(*this); }

private:
    Sprite* startSprite;
    bool isFreeze = false;
    int deadType = 0;
    bool deadAnimation = false;
    bool noAnimation = false;
    int deadTime = 0;
    int currentDir = 1;
    float speed = 60.0f;
    int delayToDie = 0;
};
