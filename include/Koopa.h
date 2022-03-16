#pragma once
#include "LivingEnt.h"

class Koopa : public LivingEnt {

public:
    ~Koopa(){}
	Koopa(Sprite* sprite,Sprite * spriteShell) : LivingEnt(0, sprite, ECol::Solid) {
        this->shellSprite = spriteShell;
    };
    void onStart();
    void onUpdate();
	bool onColide(Ent* ent,int colIndex);
    void onDead();
    Ent* clone() { return new Koopa(*this); }

private:    
    Sprite* startSprite;
    Sprite* shellSprite;
    bool isFreeze = false;
    bool deadAnimation = false;
    int deadTime = 0;
    bool noAnimation = false;
    int currentDir = 1;
    int delayToDie = 0;
    float speed = 60.0f;
    bool colided = false;
};
