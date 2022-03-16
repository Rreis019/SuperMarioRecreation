#pragma once
#include <SDL2/SDL.h>

class BaseScreen
{
public:
    //Function responsible for handling events
	virtual void events(SDL_Event events) {}

	//Function responsible for drawing on the screen
	virtual void render() {}

	//This function is called when changes from current to this
	virtual void onChangeScene(){}
private:
};
