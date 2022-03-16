#include "Ent.h"
class Lava : public Ent {

public:
	Lava(Sprite* sprite)  : Ent(0,sprite,ECol::Trigger) {};
    void onStart();
	//void onRender();
    void onUpdate();
	bool onColide(Ent* ent,int colIndex);
    Ent* clone() { return new Lava(*this); }

private:
    Sprite* startSprite;
};
