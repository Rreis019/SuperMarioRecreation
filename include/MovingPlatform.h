#pragma once
#include "Ent.h"

class MovingPlatform : public Ent {

public:

	MovingPlatform(Sprite* sprite,Vec2 vel)  : Ent(0,sprite,ECol::Solid) {
        this->velocity = vel;
    };
	void onRender();
	void onStart();
    void onUpdate();
	bool onColide(Ent* ent,int colIndex);
    Ent* clone() { return new MovingPlatform(*this); }

private:
    Vec2 velocity = Vec2(0,0);
    int sizeX = 4;
};
