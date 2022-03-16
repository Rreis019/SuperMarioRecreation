#include "Camera.h"
#include "Game.h"
#include "Input.h"
#include "World.h"
#include "Timer.h"

Camera mainCamera;
bool Camera::W2S(Ent* ent, Vec2& outPos)
{
    outPos.x = ent->pos.x - ceill(this->pos.x);
    outPos.y = ent->pos.y - ceill(this->pos.y);


    if(
        outPos.x + ent->sprite->w < 0   ||
        outPos.y + ent->sprite->h < 0   ||
        outPos.x > game.witdh  ||
        outPos.y > game.height )    
    {
        return false;
    }
    

    return true;
}


void Camera::onUpdate()
{
    return;
    float speed = 300.0f;
    if(isKeyDown(SDL_SCANCODE_W))
    {
        pos.y -= speed * timer.deltaTime;

    }
    if(isKeyDown(SDL_SCANCODE_S))
    {
        pos.y += speed * timer.deltaTime;
    }
    if(isKeyDown(SDL_SCANCODE_A))
    {
        pos.x -= speed * timer.deltaTime;
    }
    if(isKeyDown(SDL_SCANCODE_D))
    {
        pos.x += speed * timer.deltaTime;
    }
    
    if(isKeyDown(SDL_SCANCODE_B))
    {
        this->pos.y = ceill(this->pos.y);
    }
}


bool Camera::W2S(Vec2 worldPos, Vec2* outPos)
{
	outPos->x = worldPos.x - ceill(this->pos.x);
    outPos->y = worldPos.y - ceill(this->pos.y);


	return true;
}


void Camera::onRender()
{

}