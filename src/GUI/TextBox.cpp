#include "Textbox.h"
#include "Drawings.h"
#include "Game.h"

void TextBox::events(SDL_Event event)
{
	if (event.type == SDL_KEYDOWN)
	{
		isUsing = true;
		lastTimeUsed = SDL_GetTicks();

		int index = event.key.keysym.sym;
	
		switch (index)
		{
		case SDLK_RIGHT:
			if(cursorPos < text.length())
				cursorPos++;
			break;
		case SDLK_LEFT:
			if(cursorPos > 0)
				cursorPos--;
			break;
		case SDLK_BACKSPACE:
			if (text.length() > 0 && cursorPos > 0)
			{
				text.erase(cursorPos-1, 1);
				cursorPos--;
			}
			break;
		default:
			if (text.length() < maxLenght)
			{
				for (int i = 0; i < IGNORE_LETTERS_SIZE; i++)
				{
					if (index == ignoreLetters[i]) {
						return;
					}
				}

				
				char letter = (char)toupper(index);
				text.insert(cursorPos,1,letter);
				cursorPos++;
			}
			break;
		}

	}
}


void TextBox::draw()
{
	//draw bottom-border
	drawFilledRect(renderer, x, y + font->getTextH() + 2, maxLenght * font->LetterWitdh,1,{255, 255,255,255});

	//draw text
	font->draw(x, y, text);

	if (SDL_GetTicks() > lastTimeUsed + 500)
	{
		int drawCursor = (SDL_GetTicks() / 600) % 2;

		if (drawCursor == 1)
			drawFilledRect(renderer, x + font->LetterWitdh * cursorPos, y, 1, font->getTextH(),{255, 255, 255, 255});
	}
	else {
		drawFilledRect(renderer, x + font->LetterWitdh * cursorPos, y, 1, font->getTextH(), {255, 255, 255, 255});
	}
	
}

TextBox::TextBox(int x, int y, CustomFont* _font, int maxlenght)
{
	this->x = x;
	this->y = y;
	this->font = _font;
	this->maxLenght = maxlenght;
	this->cursorPos = 0;
}