#include "NewGameScreen.h"
#include "World.h"
#include "KeyGui.h"
#include <sstream>
#include "ScreenManager.h"
#include "SaveSystem.h"
#include "LevelManager.h"
#include "Utils.h"
#include "Hud.h"
#include "Logger.h"

void NewGameScreen::events(SDL_Event events)
{
    keyGui.events(events);

    if (events.type == SDL_KEYUP && events.key.keysym.sym == SDLK_ESCAPE)
    {
        screenManager.changeScreen(TITLE_SCREEN);
        world.maxPlayers = 0;
    }
}

void NewGameScreen::render()
{
    world.render();

    screenManager.sprites[0].draw(110, 15);
    keyGui.begin(150, 125);

    for(int i = 0; i < 3;i++)
    {
        if(keyGui.button(slotText[i]))
        {
            if(isSlotEmpty[i])
            {
                saveSystem.save(i,{0,0,5,0});
                hud.lifes = 5;
                hud.setScore(0);
                hud.setCoin(0);
                levelManager.currentLevel = 0;
            }
            else
            {
                SaveData data;
                saveSystem.load(i, data);
                levelManager.currentLevel = data.CurrentLevel;
                hud.lifes = data.Lives;
                hud.setCoin(data.CurrentCoins);
                hud.setScore(data.Score);
            }
            saveSystem.currentSaveSlot = i;
            screenManager.changeScreen(NEXT_LEVEL_SCREEN);
        }
    }
    keyGui.end();
}

void NewGameScreen::onChangeScene()
{
    keyGui.currentIndex = 0;
    SaveData saveData;
    for(int index = 0; index < MAX_SLOTS; index++)
    {
        std::string savePath = saveSystem.getPath(index);
        log("%s\n", savePath.c_str());
        if(!fileExists(savePath.c_str() ))
        {
            isSlotEmpty[index] = true;
            slotText[index] = "SLOT " + std::to_string(index) + " ... EMPTY";
            continue;
        }
        isSlotEmpty[index] = false;
        saveSystem.load(index, saveData);
        slotText[index] = "SLOT " + std::to_string(index) + " LEVEL " + std::to_string(saveData.CurrentLevel+1);
    }
}
