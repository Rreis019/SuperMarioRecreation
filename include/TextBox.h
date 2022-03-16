#pragma once
#include "CustomFont.h"
#include <SDL2/SDL.h>


class TextBox {
public:
	int x, y;
	CustomFont* font;
	std::string text;
	int maxLenght;
	unsigned int cursorPos = 0;


	bool isUsing = false;
	int lastTimeUsed = 0;
	
	#define IGNORE_LETTERS_SIZE 56
	int ignoreLetters[IGNORE_LETTERS_SIZE] =
	{
		SDLK_LSHIFT,
		SDLK_RSHIFT,
		SDLK_CAPSLOCK,
		SDLK_DOWN,
		SDLK_UP,
		SDLK_LCTRL,
		SDLK_KP_ENTER

	};

	TextBox() {}
	TextBox(int x, int y, CustomFont* font, int maxLength);
	void events(SDL_Event event);


	void draw();
private:

};
