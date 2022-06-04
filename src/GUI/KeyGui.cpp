#include "KeyGui.h"
#include "Logger.h"
#include "Input.h"

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
	totalMarginX = 0;
	totalMarginY = 0;

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

		if(!selectedInputKey)
		{
			if (events.key.keysym.sym == SDLK_DOWN)
				currentIndex++;
			else if (events.key.keysym.sym == SDLK_UP)
				currentIndex--;

			if (currentIndex > totalItems - 1)
				currentIndex = 0;
			else if (currentIndex < 0)
				currentIndex = totalItems - 1;
		}
		else{
			newKey = events.key.keysym.scancode;
			//log("newKey: %d\n",newKey);
		}


	}
}


bool KeyGui::inputKey(std::string text,int &key)
{
	char uppercase[32];
	if(key == 1){
		strcpy(uppercase, "MOUSE1");
	}else{
		const char* keyStr =SDL_GetKeyName(SDL_SCANCODE_TO_KEYCODE(key));
		strcpy(uppercase,keyStr);
	}
	//uppercase down
	for (int i = 0; i < strlen(uppercase); i++){
		uppercase[i] = toupper(uppercase[i]);
	}


	
	//	std::string displayText = text + " " + uppercase;
		currentFont->draw(menuX + totalMarginX, menuY + totalMarginY, text);
	
	//flickering text when is selected

	bool isHover = showSelected && currentIndex == itemIndex && selectedInputKey;

	if(!isHover){
		currentFont->draw(menuX + totalMarginX + currentFont->getTextW(text) + 5, menuY + totalMarginY, uppercase);
	}
	//}

	if (currentIndex == itemIndex)
	{
		if(selectedInputKey && newKey != -1){
			selectedInputKey = false;
			key = newKey;
			log("newKey: %d\n",key);
			newKey = -1;
		}

		if(SDL_GetTicks64() - selectedTimeInputKey > 1000){
			selectedTimeInputKey = SDL_GetTicks64();
			showSelected = !showSelected;
		}

		if (isKeyPressed(SDL_SCANCODE_RETURN)){
			selectedInputKey = true;
		}

		if(this->icon != nullptr){
			icon->draw(menuX + totalMarginX + iconX, menuY + totalMarginY);
		}
	}

	itemIndex++;
	totalMarginX += marginX;
	totalMarginY += marginY;
	return true;
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
