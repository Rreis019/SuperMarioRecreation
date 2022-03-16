#include "Ent.h"

enum EDir
{
	UP,
	LEFT,
	DOWN,
	RIGHT
};


class Teleport : public Ent {

public:

	Teleport(Vec2 pos,int changeScene,Vec2 destPos,int dir);
    void onStart();
	void onRender();
    void onUpdate();
	bool onColide(Ent* ent,int colIndex);
    Ent* clone() { return new Teleport(*this); }
private:
    void changeScene();
    Ent* player;
    int nextScene = 0;
    bool canTeleport = false;
    Vec2 destPos;
    int dir = 0;
};
