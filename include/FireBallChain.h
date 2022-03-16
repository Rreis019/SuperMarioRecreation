#include "Ent.h"
class FireBallChain : public Ent {

public:

	FireBallChain(Sprite* sprite)  : Ent(LFIREBALCHAIN,sprite,ECol::Solid) {};
    void onStart();
	void onRender();
    void onUpdate();
	bool onColide(Ent* ent,int colIndex);
    Ent* clone() { return new FireBallChain(*this); }

private:
    int chainLength = 6;
    float chainAngle = 0;
};
