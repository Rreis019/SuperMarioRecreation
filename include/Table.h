#pragma once
#include "Vec2.h"
#include <string>
#include <vector>
#include <SDL2/SDL.h>

class Collum
{
	public:
	Collum(std::string name, int w)
	{
		this->name = name;
		this->w = w;
	}
	std::string name = "";
	int w = 0;
};



class Table
{
public:
	Table() {
	}
	SDL_Color backgrondColor = { 0,0,0,255 };
	int x = 0, y = 0;
	std::vector<Collum> cols =  std::vector<Collum>();
	std::vector<std::string> items = std::vector<std::string>();

	bool drawBorder = false;
	bool drawHeader = false;
	int headerSize = 20;
	int colSize = 20;

	void addCollum(std::string name, int w);
	void addItem(std::string value);
	void draw();

private:
};