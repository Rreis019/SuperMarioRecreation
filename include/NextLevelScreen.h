#pragma once
#include "BaseScreen.h"
#include "Sprite.h"

class NextLevelScreen : public BaseScreen
{
public:
	~NextLevelScreen();
    void events(SDL_Event events);
	void render();
	void onChangeScene();
private:
	#define DELAY_NEXT_LEVEL 1000
	int nextLevelTime = 0;
	std::string displayName = "";
	std::vector<Sprite> sprites;
};
