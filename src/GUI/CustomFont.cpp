#include "Customfont.h"
#include <SDL2/SDL_image.h>
#include "Game.h"

CustomFont defaultFont;

CustomFont::CustomFont(std::string Letters, std::string pathImage, int width, int height)
{
	AllLetters = Letters;
	LetterWitdh = width;
	LetterHeight = height;
    loadSpriteSheet(LetterImg, pathImage.c_str());
}


void CustomFont::draw(int x,int y,std::string text)
{
	for (int i = 0; i < (int)text.length(); i++)
	{
		auto index = AllLetters.find(text[i]);

		if (index == std::string::npos)
			continue;

		LetterImg[index].draw(x + i * LetterWitdh, y);
	}
}