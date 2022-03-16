#include "Ent.h"
class Flower : public Ent {

public:

	Flower(Sprite* sprite)  : Ent(0,sprite,ECol::Trigger) {};
    void onStart();
	//void onRender();
    //void onUpdate();
	bool onColide(Ent* ent,int colIndex);
    Ent* clone() { return new Flower(*this); }

private:
};
