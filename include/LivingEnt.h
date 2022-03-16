#pragma once
#include "Ent.h"
#include "Vec2.h"

class LivingEnt : public Ent
{
    public:
        LivingEnt(){};
        LivingEnt(int layer, Sprite* sprite, ECol ecol) : Ent(layer, sprite, ecol){};
        Vec2 velocity = Vec2(0,0);
        bool isGrounded = false;
        bool noColision = false;
        bool checkCollisionX();
        bool checkCollisionY();
    private:
};