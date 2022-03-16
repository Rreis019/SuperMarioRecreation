#include "Lava.h"
#include "Timer.h"

void Lava::onStart()
{
    startSprite = sprite;
}

void Lava::onUpdate()
{
    this->sprite = startSprite + ANIMATION(0,8,150);
}

bool Lava::onColide(Ent* ent,int colIndex)
{

}