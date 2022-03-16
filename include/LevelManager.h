#pragma once
#include <string>
#include <map>
#include "Vec2.h"

//typedef void command();
typedef void (*tpCommand)(std::string line);

class LevelManager
{
    public:
    LevelManager();
    int currentLevel = 0;
    void loadLevel(int level);
    void loadLevel(std::string levelName);
    bool isReadingTileMap = false;// ex: "0 0 1 0 0 "


    int levelY = 0;
    int numScene = 0;
    Vec2 startPos;
    Vec2 finalPos;
    
    std::string displayName;
    std::map<std::string, tpCommand> commands;
    std::string levelPath;
    private:
};

extern LevelManager levelManager;