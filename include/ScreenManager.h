#pragma once
#include <vector>
#include "BaseScreen.h"
#include "Sprite.h"

enum EScreen
{
    SCREEN_NONE = -1,
    TITLE_SCREEN,
    OPTIONS_SCREEN,
    NEW_GAME_SCREEN,
    NEXT_LEVEL_SCREEN,
    SCOREBOARD_SCREEN,
    GAME_SCREEN,
    GAME_OVER_SCREEN,
    SCOREBOARD_SELECTION_SCREEN,
    SUBMIT_SCORE_SCREEN,
    INPUT_CONTROLS_SCREEN,
    PLAYER_CONTROLS_SCREEN,
    VIDEO_SCREEN,
    AUDIO_SCREEN
};

class ScreenManager
{
public:
    ScreenManager();
    ~ScreenManager();
    void init();
    void changeScreen(EScreen index);
    void updateChanges();
    BaseScreen* getCurrentScreen();
    std::vector<Sprite> sprites;
private:
    std::vector<BaseScreen*> screens;
    EScreen nextScreen = EScreen::SCREEN_NONE;
    EScreen currentScreen = TITLE_SCREEN;

};

extern ScreenManager screenManager;