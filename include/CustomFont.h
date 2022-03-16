#pragma once
#include <vector>
#include "Sprite.h"
#include <string>

class CustomFont
{
public:
	std::vector<Sprite> LetterImg = std::vector<Sprite>();
	std::string AllLetters = "";
	int LetterWitdh = 0, LetterHeight = 0;
	//a,b,c,d,s,z

	CustomFont(){}
	CustomFont(std::string Letters, std::string pathImage, int width, int height);
	void draw(int x, int y,std::string text);
	
	int getTextW(std::string name) { return LetterWitdh * name.length(); }
	int getTextH() { return LetterHeight; }

private:
};

extern CustomFont defaultFont;