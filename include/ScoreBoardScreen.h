#pragma once
#include "BaseScreen.h"
#include "Sprite.h"
#include "Table.h"


class ScoreBoardScreen : public BaseScreen
{
public:

    void events(SDL_Event events);
	void render();
	void onChangeScene();
private:
};

extern bool isScoreBoardOnline;