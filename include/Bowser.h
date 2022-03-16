#pragma once
#include "LivingEnt.h"

enum EBowserAnimation{
    EBOWSER_IDLE,
    ETAKINGDAMAGE,
    EATTACKING,
};

class Bowser : public LivingEnt {
public:
    ~Bowser(){}
	Bowser(Sprite* sprite) : LivingEnt(0, sprite, ECol::Solid) {};
	//void onRender();
    void onStart();
    void onUpdate();
	bool onColide(Ent* ent,int colIndex);
    void onDead();
    Ent* clone() { return new Bowser(*this); }

private:
    Sprite* startSprite;
    int health = 5;
	int Limit = 16* 5;
    int dirX = -1;
    EBowserAnimation currentAnimation = EBOWSER_IDLE;
    float fireballTime = 1.0f; // delay between fireballs
    float takeDamageTime = 0.2f;
    float openMouthTime = 0.2f;
    float closeMouthTime = 0.2f;
    bool sendFireball = false;
    bool deadAnimation = false;
    Vec2 startPos;
};
