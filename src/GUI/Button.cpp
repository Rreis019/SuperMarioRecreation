#include "Input.h"
#include "Button.h"
#include <SDL2/SDL.h>


Button::Button(Vec2 pos,const char* buttonSpritePath,const char* buttonSpriteHoverPath)
{
    this->position = pos;
    this->buttonSprite = new Sprite(buttonSpritePath);
    this->buttonSpriteHover = new Sprite(buttonSpriteHoverPath);
}

bool Button::isMouseOver()
{
    Vec2 mousePos = getMousePos();
    Vec2 size = Vec2(buttonSprite->w,buttonSprite->h);
    return (mousePos.x > position.x && mousePos.x < position.x + size.x && mousePos.y > position.y && mousePos.y < position.y + size.y);
}

bool Button::draw()
{
    if(isMouseOver()){
        buttonSpriteHover->draw(position.x,position.y); 
        SDL_SetCursor(SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_HAND));
        if(isleftMouseClicked()){
            return true;
        }
        return false;
    }
    buttonSprite->draw(position.x,position.y);
    SDL_SetCursor(SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_ARROW));
    return false;
}
