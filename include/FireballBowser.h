#include "Ent.h"
class FireballBowser : public Ent {

public:
	FireballBowser(Sprite* sprite,int dir)  : Ent(0,sprite,ECol::Trigger) { this->direction = dir; };
    void onStart();
    void onUpdate();
	bool onColide(Ent* ent,int colIndex);
    Ent* clone() { return new FireballBowser(*this); }

private:
    int direction = 1;
    Sprite* startSprite;
    float lifeTime = 1.5f;
};
