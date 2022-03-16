#pragma once
#include "Vec2.h"
#include "Ent.h"
class Camera : public Ent
{
public:
    Camera(){}
    void onUpdate();
    void onRender();
	bool W2S(Ent* ent, Vec2& outPos);
    bool W2S(Vec2 worldPos, Vec2* outPos);
};

extern Camera mainCamera;