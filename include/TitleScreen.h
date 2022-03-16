#pragma once
#include "BaseScreen.h"
#include "Sprite.h"

class TitleScreen : public BaseScreen
{
public:
    void events(SDL_Event events);
	void render();
	void onChangeScene();
private:
};
