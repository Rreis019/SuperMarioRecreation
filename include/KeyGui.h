#pragma once
#include "Customfont.h"


class KeyGui
{
public:
	CustomFont* currentFont;
	Sprite* icon;//Icon que fica ao lado do texto quando esta selecionado
	int iconX = -10;//Posição label + IconX

	int menuX = 0;
	int menuY = 0;
	int marginX = 0;
	int marginY = 20;
	bool drawIcon = false;

	void begin(int x, int y);
	void events(SDL_Event events);
	void end();

	void setMenuPos(int x, int y);

	void label(std::string text);

	bool button(std::string text);

	bool toggle(std::string text, bool* enable);

	bool numericInt(std::string text, int* num, int minN, int maxN);

	void setIndexZero() { this->currentIndex = 0; };

    KeyGui(){}
    KeyGui(CustomFont* font, Sprite* icon,int marginX,int marginY);

	int  currentIndex = 0;
private:
	int  itemIndex = 0;
	int  totalItems = 0;
	int  totalMarginX = 0, totalMarginY = 0;
	bool pressedEnter = false;
	bool pressedLeft = false;
	bool pressedRight = false;
};

extern KeyGui keyGui;