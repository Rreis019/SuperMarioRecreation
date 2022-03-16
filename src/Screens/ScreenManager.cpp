#include "ScreenManager.h"
#include <Windows.h>

//SCREENS
#include "TitleScreen.h"
#include "OptionsScreen.h"
#include "NextLevelScreen.h"
#include "ScoreBoardScreen.h"
#include "GameScreen.h"
#include "NewGameScreen.h"
#include "GameOverScreen.h"
#include "ScoreBoardSelection.h"
#include "SubmitScoreScreen.h"

ScreenManager screenManager;

ScreenManager::ScreenManager()
{
    screens.push_back(new TitleScreen());
    screens.push_back(new OptionsScreen());
    screens.push_back(new NewGameScreen());
    screens.push_back(new NextLevelScreen());
    screens.push_back(new ScoreBoardScreen());
    screens.push_back(new GameScreen());
    screens.push_back(new GameOverScreen());
    screens.push_back(new ScoreBoardSelection());
    screens.push_back(new SubmitScoreScreen());
}

ScreenManager::~ScreenManager(){}

void ScreenManager::changeScreen(EScreen index){nextScreen = index;}
void ScreenManager::init(){
    loadMultipleImages(sprites,"Resources/Screens/TitleScreen/","StartMenu_");
}

void ScreenManager::updateChanges()
{
    if(nextScreen != SCREEN_NONE)
    {
        currentScreen = nextScreen;
        nextScreen = SCREEN_NONE;
        screens[(int)(currentScreen)]->onChangeScene();
    }
}

BaseScreen* ScreenManager::getCurrentScreen(){return screens[(int)(currentScreen)];}
