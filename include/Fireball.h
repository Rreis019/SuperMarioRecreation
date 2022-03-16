#include "LivingEnt.h"
class Fireball : public LivingEnt {

public:

	Fireball(Sprite* sprite,int dir)  : LivingEnt(0,sprite,ECol::Solid) { this->direction = dir; };
    void onStart();
	//void onRender();
    void onUpdate();
	bool onColide(Ent* ent,int colIndex);
    Ent* clone() { return new Fireball(*this); }

private:
    int direction = 1;
    Sprite* startSprite;
};
