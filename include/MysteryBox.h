#pragma once
#include "Ent.h"


enum EHoldItem
{
    EHoldNone = -1,
    EHoldCoin,
    EHoldMushroom,
    EHoldFlower,
    EHoldStar
};


class MysteryBox : public Ent 
{
public:

	MysteryBox(Sprite* sprite,EHoldItem holdItem)  : Ent(0,sprite,ECol::Solid) {
        this->holdItem = holdItem;
    };
	void onRender();
    void onStart();
    void onUpdate();
	bool onColide(Ent* ent,int colIndex);
    Ent* clone() { return new MysteryBox(*this); }
private:
    bool isEmpty = false;
    bool shakeUp = false;
    bool shakeDown = false;
    EHoldItem holdItem = EHoldItem::EHoldNone;

    float elapsedTime = 0.0f;
    float startY = 0;
    Sprite* startSprite;
};
