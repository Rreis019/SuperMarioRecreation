#include "World.h"
#include "Prefabs.h"
#include "Game.h"
#include <algorithm>
#include <cassert>
#include "SoundManager.h"
#include "Logger.h"
World world;

void World::init()
{
    world.scenes.push_back(Scene());
    world.scenes.push_back(Scene());
    loadPrefabs();
    currentCamera = &mainCamera;
}

Ent*  World::getEnt(int index) 
{
    return scenes[currentScene].entities[index];
}

Scene* World::getScene(int index){
    return &scenes[index];
}


Scene* World::getCurrentScene()
{
    return &scenes[currentScene];
}

void World::update()
{
    if(game.isPaused) { return;}

    if (scenes.size() == 0) return;
    
    //remove dead entities
    for (int i = 0; i < getEntityCount();i++)
    {
        Ent * ent = getEnt(i);
        if (getEnt(i)->isAlive == false)
        {
            if(ent->tag == TController){continue;}
            if(ent == nullptr){continue;}
            delete ent;
            ent = nullptr;
            getCurrentScene()->entities.erase(world.getCurrentScene()->entities.begin() + i);
            i--;

        }
    }


    for(int i = 0; i < (int)scenes[currentScene].entities.size(); i++)
    {
        scenes[currentScene].entities[i]->onUpdate();
    }




    currentCamera->onUpdate();
}

void World::render()
{
    if (scenes.size() == 0) return;

    //Render backgrounds
    for(int i = 0; i < (int)scenes[currentScene].numBackgrounds; i++)
    {

        scenes[currentScene].backgrounds[i]->draw();
    }

    for(int i = 0; i < (int)scenes[currentScene].entities.size(); i++)
    {
        scenes[currentScene].entities[i]->onRender();
    }

    
    if(nextScene != -1){
        this->currentScene = nextScene;
        if(scenes[currentScene].musicName != ""){
            soundManager.playMusic(scenes[currentScene].musicName,1);
        }
        nextScene = -1;
    }
}

void World::addEntity(Ent* entity,int numScene)
{
    scenes[numScene].entities.push_back(entity);
    entity->onStart();
}

void World::addEntity(Ent* entity)
{
    scenes[currentScene].entities.push_back(entity);
    entity->onStart();
}

void World::changeScene(int numScene)
{
    this->nextScene = numScene;
}


void World::clear()
{
    for(int i = 0; i < (int)scenes.size(); i++)
    {
        for(int j = 0; j < (int)scenes[i].entities.size(); j++)
        {
            if(scenes[i].entities[j]->tag == TController){continue;}
            delete scenes[i].entities[j];
        }
        scenes[i].entities.clear();
        this->clearBackgrounds(i);
    }

    controllers.clear();
    scenes.clear();
    this->currentScene = 0;
    this->scenes.push_back(Scene());
    currentCamera->pos = Vec2(0,0);
}


void World::addBackground(std::string path,int scene)
{
    if(scenes[scene].numBackgrounds >= MAX_BACKGROUNDS){
        log("Max backgrounds reached");
        return;
    }

    ScrollBackground* background = new ScrollBackground(path.c_str());
    scenes[scene].backgrounds[scenes[scene].numBackgrounds] = background;
    scenes[scene].numBackgrounds++;
}

void World::clearBackgrounds(int scene)
{
    for(int i = 0 ; i < this->scenes[scene].numBackgrounds; i++)
    {
        SDL_DestroyTexture(scenes[scene].backgrounds[i]->background.texture);
        scenes[scene].backgrounds[i]->background.texture = nullptr;
        //   ScrollBackground* backgrounds[MAX_BACKGROUNDS] = { nullptr, nullptr };
        delete scenes[scene].backgrounds[i];
    }
}
