#pragma once
#include <string>


#define SAVE_FOLDER_NAME "SuperMarioSaves"

struct SaveData
{
    int CurrentLevel;
    int Score;
    int Lives;
    int CurrentCoins;
};

class SaveSystem
{
public:
    SaveSystem();
    std::string getPath(int index);

    void init();
    void save(int index, SaveData data);
    void load(int index, SaveData& data);
    void del(int index);

    int currentSaveSlot = 0;
private:
    std::string saveDirPath = "";
};

extern SaveSystem saveSystem;
