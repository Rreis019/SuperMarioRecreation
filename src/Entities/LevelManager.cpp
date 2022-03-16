#include "LevelManager.h"
#include <fstream>
#include <vector>
#include "Utils.h"
#include <sstream> 
#include "World.h"
#include "Prefabs.h"
#include "Controller.h"

#include <algorithm>
#include <iostream>
#include "Teleport.h"
#include "Game.h"
#include "SoundManager.h"
#include "Logger.h"

LevelManager levelManager;

//Commands
void startScene(std::string line)
{ 
    levelManager.isReadingTileMap = true;
    levelManager.levelY = 0;
    world.addScene();
}
void endScene(std::string line){ levelManager.isReadingTileMap = false; levelManager.numScene++; }

void teleport(std::string line){
    //Teleporte = 200, 200,0,2600,154,3
    //split space
    std::vector<std::string> tokens;
    strSplit(line, "=", tokens);
    std::string temp = tokens[1];tokens.clear();
    strSplit(temp, ",", tokens);

    for(size_t i = 0; i < tokens.size(); i++){
        strRemoveChar(tokens[i], ' ');
        log("%s\n", tokens[i].c_str());
    }
    Vec2 pos = Vec2(std::stof(tokens[0]), std::stof(tokens[1]));
    int changeScene = std::stoi(tokens[2]);
    Vec2 destPos = Vec2(std::stof(tokens[3]), std::stof(tokens[4]));
    int dir = std::stoi(tokens[5]);

    Teleport* teleport = new Teleport(pos, changeScene, destPos, dir);
    world.addEntity(teleport,levelManager.numScene);
}

void music(std::string line)
{
    //Music = 05.overworld.mp3
    std::vector<std::string> tokens;
    strSplit(line, "=", tokens);
    strRemoveChar(tokens[1], ' ');
    log("scene %d music loaded: %s\n",levelManager.numScene, tokens[1].c_str());
    world.getScene(levelManager.numScene)->musicName =  tokens[1];
}

void background(std::string line)
{
    std::vector<std::string> tokens;
    strSplit(line, "=" , tokens);
    strRemoveChar(tokens[1], ' ');
    world.addBackground(tokens[1].c_str(), levelManager.numScene);
    log("scene %d background loaded: %s\n",levelManager.numScene, tokens[1].c_str());
}


void startPlayerPos(std::string line)
{
    //PlayerPos = 16,150
    std::vector<std::string> tokens;
    strSplit(line, "=", tokens);
    strRemoveChar(tokens[1], ' ');
    strSplit(tokens[1], ",",tokens);
    levelManager.startPos = Vec2(atoi(tokens[0].c_str()),atoi(tokens[1].c_str()));
}


void finalPlayerPos(std::string line)
{
    //Final=3254,160
    std::vector<std::string> tokens;
    strSplit(line, "=", tokens);
    strSplit(tokens[1], ",",tokens);
    levelManager.finalPos = Vec2(atoi(tokens[0].c_str()),atoi(tokens[1].c_str()));
}


LevelManager::LevelManager()
{
    //Setup commands
    commands["PlayerPos"] =  startPlayerPos;
    commands["Final"] =  finalPlayerPos;
    commands["StartScene"] =  startScene;
    commands["EndScene"] =  endScene;
    commands["Teleport"] =  teleport;
    commands["Music"] =  music;
    commands["Background"] =  background;
}

bool updateCommands(std::string line)
{
    for(auto it = levelManager.commands.begin(); it != levelManager.commands.end(); ++it)
    {
        if((int)line.find(it->first) != -1)
        {
            it->second(line);
            return true;
        }
    }
    return false;
}

void LevelManager::loadLevel(int level)
{
    currentLevel = level;
    char lvlName[100];  sprintf(lvlName, "Resources/Levels/Level%d.txt", levelManager.currentLevel+1);
    loadLevel(lvlName);
    
}
void LevelManager::loadLevel(std::string levelName)
{
    levelPath = levelName;
    world.clear();
    std::ifstream readFile;
    std::string line;
    readFile.open(levelName);
    numScene = 0;

    if(!readFile.is_open()){ return;}
 
    while(std::getline(readFile,line))
    {
        if(updateCommands(line)){ continue; }

        if(isReadingTileMap)
        {
            std::vector<std::string> arr = std::vector<std::string>();
            strSplit(line, " ", arr);
            
            for(int x = 0; x < (int)arr.size(); x++)
            {
                int tile = std::stoi(arr[x]);
                if(tile < 0){ continue; }
                Ent* e = getPrefab(tile, x*16, levelY*16);
                world.addEntity(e,numScene);
            }
            levelY++;
        }
    }
    readFile.close();

    world.numPlayers = world.maxPlayers;



    for(int i = 0 ; i < world.numPlayers; i++){
        Controller* player;
        
        if((i+1)%2 == 0)
            player = new Controller(&player1Controls,(char*)"Luigi");
        else
            player = new Controller(&player2Controls,(char*)"Mario");

        if(i == 0){player->followCamera =  world.currentCamera;}
        player->pos = startPos;
        player->centerCamera();


        for(int j = 0; j < levelManager.numScene+1; j++){
            world.addEntity(player,j);

        }

        world.controllers.push_back(player);
    }



    //loop throught all scenes and sort the entities by layers
    for(int i = 0; i < numScene; i++){
        std::sort(world.getScene(i)->entities.begin(), world.getScene(i)->entities.end(), [](Ent* a, Ent* b){
            return a->layer < b->layer;
        });
    }

    Scene *scene = world.getScene(0); 
    soundManager.playMusic(scene->musicName,1);
}