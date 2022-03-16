#pragma once
#include "Sprite.h"
#include "Camera.h"
class ScrollBackground
{
public:
	//Camera relative to the background
	Camera camera = Camera();
    ~ScrollBackground();
	ScrollBackground() {}
	ScrollBackground(const char* filename);

	ScrollBackground(const char* filename, SDL_Color transparent)
	{
		this->background = Sprite(filename, transparent);
	}

	void scrollX(float valor)
	{
		this->camera.pos.x -= valor;
	}

	void draw();

	Sprite background;
private:
};

