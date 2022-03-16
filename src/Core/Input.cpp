#include "Input.h"
#include <string.h>
#include <stdio.h>
#include <cassert>

#define MAX_KEYS 256
bool KeysDown[MAX_KEYS];
bool KeysPressed[MAX_KEYS];
bool leftButtonDown = false;
bool rightButtonDown = false;
bool leftButtonUp = false, rightButtonUp = false;
int mousePosX = 0, mousePosY = 0;

void inputEvents(SDL_Event& event)
{
	switch (event.type)
    {	
		case SDL_KEYDOWN:
    	 	if(event.key.keysym.scancode < MAX_KEYS)
    	 	{
				KeysDown[event.key.keysym.scancode] = true;
    	 	}

            break;
		case SDL_KEYUP:
    	 	if(event.key.keysym.scancode < MAX_KEYS)
    	 	{
				KeysDown[event.key.keysym.scancode] = false;
				KeysPressed[event.key.keysym.scancode] = true;
    	 	}
        	break;
		case SDL_MOUSEBUTTONDOWN:
			if(event.button.button == SDL_BUTTON_LEFT)
				leftButtonDown = true;
			else if(event.button.button == SDL_BUTTON_RIGHT)
				rightButtonDown = true;
			break;
		case SDL_MOUSEBUTTONUP:
			if(event.button.button == SDL_BUTTON_LEFT)
			{
				leftButtonDown = false;
				leftButtonUp = true;
			}
			else if(event.button.button == SDL_BUTTON_RIGHT)
			{
				rightButtonDown = false;
				rightButtonUp = true;
			}
			break;
		case SDL_MOUSEMOTION:
			mousePosX = event.motion.x;
			mousePosY = event.motion.y;
			break;


    }
}


void inputReset() 
{ 
    leftButtonUp = false;
    rightButtonUp = false;
    memset(KeysPressed, 0, sizeof(KeysPressed)); 
}

bool isKeyDown(int index) { return KeysDown[index]; }
bool isKeyPressed(int index) {  return KeysPressed[index]; }
bool isLeftButtonDown() { return leftButtonDown; }
bool isRightButtonDown() { return rightButtonDown; }
Vec2 getMousePos() { return Vec2(mousePosX, mousePosY); }
bool isleftMouseClicked() { return leftButtonUp; }
bool isRightMouseClicked() { return rightButtonUp; }
