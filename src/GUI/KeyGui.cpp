#include "KeyGui.h"

KeyGui keyGui;

KeyGui::KeyGui(CustomFont* font, Sprite* icon,int marginX,int marginY)
{
    this->currentFont = font;
    this->icon = icon;
    this->marginX = marginX;
    this->marginY = marginY;
    this->currentIndex = 0;
}

void KeyGui::begin(int x, int y)
{
	menuX = x;
	menuY = y;
	totalItems = 0;
	itemIndex = 0;

}

void  KeyGui::setMenuPos(int x, int y)
{
	menuX = x;
	menuY = y;
	totalMarginX = 0;
	totalMarginY = 0;
}

void  KeyGui::label(std::string text)
{
	currentFont->draw(menuX + totalMarginX, menuY + totalMarginY, text);
	totalMarginX += marginX;
	totalMarginY += marginY;
}

bool  KeyGui::button(std::string text)
{
	bool result = false;
	currentFont->draw(menuX + totalMarginX, menuY + totalMarginY, text);

	if (currentIndex == itemIndex)
	{
		if (pressedEnter)
			result = true;

		if(this->icon != nullptr){
		icon->draw(menuX + totalMarginX + iconX, menuY + totalMarginY);
		}
	}

	itemIndex++;
	totalMarginX += marginX;
	totalMarginY += marginY;

	return result;
}

bool  KeyGui::toggle(std::string text, bool* enable)
{
	bool result = false;
	if (*enable)
		text += " ON";
	else
		text += " OFF";

	currentFont->draw(menuX + totalMarginX, menuY + totalMarginY, text);

	if (currentIndex == itemIndex)
	{
		if (pressedEnter)
		{
			result = true;
			*enable = !*enable;
		}
		
		if(this->icon != nullptr){
		icon->draw(menuX + totalMarginX + iconX, menuY + totalMarginY);}
	}

	itemIndex++;
	totalMarginX += marginX;
	totalMarginY += marginY;

	return result;
}


bool KeyGui::numericInt(std::string text, int* num, int minN, int maxN)
{
	bool result = false;
	text += " " + std::to_string(*num);

	currentFont->draw(menuX + totalMarginX, menuY + totalMarginY, text);

	if (currentIndex == itemIndex)
	{
		if (pressedLeft)
		{
			*num -= 1;
			result = true;
		}
			
		else if (pressedRight)
		{
			*num += 1;
			result = true;
		}
			


		if (*num > maxN)
			*num = minN;
		else if (*num < minN)
			*num = maxN;

		if(this->icon != nullptr){
		icon->draw(menuX + totalMarginX + iconX, menuY + totalMarginY);}
	}

	itemIndex++;
	totalMarginX += marginX;
	totalMarginY += marginY;

	return result;
}

void  KeyGui::events(SDL_Event events)
{
	if (events.type == SDL_KEYUP)
	{
		if (events.key.keysym.sym == SDLK_RETURN)
			pressedEnter = true;
		else if (events.key.keysym.sym == SDLK_LEFT)
			pressedLeft = true;
		else if (events.key.keysym.sym == SDLK_RIGHT)
			pressedRight = true;

		if (events.key.keysym.sym == SDLK_DOWN)
			currentIndex++;
		else if (events.key.keysym.sym == SDLK_UP)
			currentIndex--;

		if (currentIndex > totalItems - 1)
			currentIndex = 0;
		else if (currentIndex < 0)
			currentIndex = totalItems - 1;
	}
}

void KeyGui::end()
{
	totalItems = itemIndex;
	//Events();
	totalMarginX = 0;
	totalMarginY = 0;
	pressedEnter = false;
	pressedLeft = false;
	pressedRight = false;
}
