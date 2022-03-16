#include "SubmitScoreScreen.h"
#include "ScreenManager.h"
#include "CustomFont.h"
#include "Button.h"
#include "ScoreSave.h"
#include "TextBox.h"
#include "SaveSystem.h"
#include "Hud.h"
#include "Logger.h"

Button* submitButton = nullptr;
TextBox submitTextbox;

void SubmitScoreScreen::events(SDL_Event events){submitTextbox.events(events);}

void SubmitScoreScreen::render()
{
    defaultFont.draw(130, 60, "ENTER YOUR NAME :");
    submitTextbox.draw();
    if(submitButton->draw()){
        if(submitTextbox.text.length() > 0){
            scoreSave.saveOnline((char*)submitTextbox.text.c_str(),hud.getScore());
            scoreSave.saveLocal((char*)submitTextbox.text.c_str(),hud.getScore());
            screenManager.changeScreen(TITLE_SCREEN);
        }
    } 
}

void SubmitScoreScreen::onChangeScene()
{
    saveSystem.del(saveSystem.currentSaveSlot);
    if(submitButton ==nullptr)
        submitButton = new Button(Vec2(160,120), "Resources/GUI/Bt_submit.png", "Resources/GUI/Bt_submit_hoverED.png");
    submitTextbox = TextBox(115, 90, &defaultFont, 20);
    log("game over\n");
}

