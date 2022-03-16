#pragma once
#include "Sprite.h"
#include "Vec2.h"


class Button
{
    public:
        Vec2 position;
        Button(){}
        Button(Vec2 pos,const char* buttonSpritePath,const char* buttonSpriteHoverPath);

        bool draw();
        private:
        bool isMouseOver();
        Sprite * buttonSprite;
        Sprite * buttonSpriteHover;

};