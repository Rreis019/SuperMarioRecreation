#include "Table.h"
#include "Game.h"
#include "Drawings.h"
#include "CustomFont.h"

void Table::addCollum(std::string name, int w) {
   this->cols.push_back({ name,w });
}

void Table::addItem(std::string value) {
	this->items.push_back(value);
}

void Table::draw()
{
	//int thickness = 1;
	//if (!drawBorder) { thickness = 0; }
	if (!drawHeader) { headerSize = 0; }

	//DrawFilledRect(renderer, x, y, 0, 0, backgrondColor.r, backgrondColor.g, backgrondColor.b, backgrondColor.a);


	int TotalX = 0;
	for (auto c : this->cols)
	{
		//drawRect(x + TotalX, y, c.w, colSize, thickness,{255, 0, 0});

		int textLength = defaultFont.getTextW(c.name);

		defaultFont.draw(
			x + TotalX + c.w / 2 - (textLength / 2), //centeredX
			y + colSize / 2 - defaultFont.getTextH() / 2, //centeredY
			c.name);

		TotalX += c.w;
	}


	int MarginLeftItem = 5;

	//Draw items
	TotalX = 0;
	int TotalY = 0;
	int TotalCols = 0;
	for (int i = 0; i < (int)items.size(); i++)
	{
		//int ItemX = x + TotalX;
		//int ItemY = y + TotalY + colSize;
		//drawRect(renderer, ItemX, ItemY, cols[TotalCols].w, colSize, thickness, 255, 0, 0, 255); //border


		defaultFont.draw(
			x + TotalX + MarginLeftItem,
			y + TotalY + headerSize + colSize / 2 - defaultFont.getTextH() / 2
			, items[i]
		);


		TotalX += cols[TotalCols].w;
		TotalCols++;
		if (TotalCols == (int)cols.size())
		{
			TotalY += colSize;
			TotalX = 0;
			TotalCols = 0;
		}
	}


}

