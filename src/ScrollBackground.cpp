#include "ScrollBackground.h"


ScrollBackground::ScrollBackground(const char* filename)
{
	this->background = Sprite(filename);
	this->camera = Camera();
	camera.pos.x = 0;
	camera.pos.y = 0;
}

void ScrollBackground::draw()
{
	camera.pos.x = (int)camera.pos.x % (this->background.w);
	int Arr[] = {0, -background.w,background.w };
	Vec2 out;

	for (int i = 0; i <  3; i++)
	{
		if (camera.W2S(Vec2(Arr[i], 0), &out))
		{
			this->background.draw(out.x,out.y);
		}
	}
}

ScrollBackground::~ScrollBackground(){
	
}