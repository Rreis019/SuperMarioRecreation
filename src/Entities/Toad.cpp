#include "Toad.h"
#include "Timer.h"
#include "World.h"
#include "CustomFont.h"
#include "ScreenManager.h"

#define JUMP_DELAY 1.0f
#define NEXT_LETTER_DELAY 0.2f

void Toad::onStart()
{
    this->tag = ETags::TToad;
    this->startSprite = this->sprite;
    numberOfLetters = 0;
}

void Toad::onUpdate()
{
    this->velocity.y +=  pow(world.gravity,2) * timer.deltaTime;
    this->pos.y += this->velocity.y * timer.deltaTime;
    if(this->checkCollisionY()){
        if(this->isGrounded)
        {
            if(jumpTime <= 0){
                this->velocity.y -= 350;
                this->jumpTime = JUMP_DELAY;
                this->sprite = startSprite+1;
            }
            else{
                this->sprite = startSprite;
            }
        }
    }

    jumpTime -= timer.deltaTime;

}


void Toad::onRender(){

    Vec2 out = {0,0};
    if(world.currentCamera != NULL){
        if(world.currentCamera->W2S(this, out)){
            this->drawColiders(out);
            this->sprite->draw(out.x,out.y,flip);
        }
    }
    else{ 
        out = this->pos;   this->drawColiders(out);
        this->sprite->draw(out.x,out.y,flip);
    }    


    if(timeNextLetter <= 0){
        timeNextLetter = NEXT_LETTER_DELAY;
        if(numberOfLetters <= finalText.size()){
            numberOfLetters++;
        }
    }

    std::string temp = finalText.substr(0,numberOfLetters);
    defaultFont.draw(95,70,temp);
    timeNextLetter -= timer.deltaTime;
    if(numberOfLetters > finalText.size()){
        defaultFont.draw(185,90,"END");
        waitToNextScreen -= timer.deltaTime;
        if(waitToNextScreen <= 0){
            screenManager.changeScreen(EScreen::SUBMIT_SCORE_SCREEN);
        }
    }

}

bool Toad::onColide(Ent* ent,int colIndex)
{
    return true;
}