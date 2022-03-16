#pragma once
#include "Ent.h"

class Flag : public Ent {

public:

	Flag(Sprite* sprite)  : Ent(0,sprite,ECol::Trigger) {};
    void onStart();
	void onRender();
    void onUpdate();
	
    bool onColide(Ent* ent,int colIndex);
    Ent* clone() { return new Flag(*this); }

private:
    int sizeY = 9;
    float flagY = 0;

    Ent* playersOnFlag = nullptr;
    bool isPlayerFlagDown = false;//indica se o player esta descer a bandeira
    int timeFlagDown = 0;

    bool removeHook = false;
    bool nextLevel = false;
    int nextTime = 0;
};
