#pragma once
#include <vector>
#include "Ent.h"
#include "Sprite.h"
#include "Camera.h"
#include "ScrollBackground.h"
#include <SDL2/SDL_mixer.h>

#define MAX_BACKGROUNDS 2

struct Scene
{
    std::vector<Ent*> entities = {};
    int numBackgrounds = 0;
    ScrollBackground* backgrounds[MAX_BACKGROUNDS] = { nullptr, nullptr };
    std::string musicName = "";
};

class World
{
    public:
        void init();
        void update();
        void render();
        void clear();

        //ENTITY FUNCTIONS
        void addEntity(Ent* entity,int scene);
        void addEntity(Ent* entity);
        void removeEntity(Ent* entity,int scene);
        int  getEntityCount() {return scenes[currentScene].entities.size();}
        Ent* getEnt(int index);

        //SCENE FUNCTIONS
        Scene* getCurrentScene();
        int getScene(){return currentScene;}
        Scene* getScene(int index);
        void changeScene(int scene);
        void addScene(){scenes.push_back(Scene());}

        //BACKGROUND FUNCTIONS
        void addBackground(std::string path,int scene);
        void clearBackgrounds(int scene);


        float gravity = 45.0f;
        int numPlayers = -1;
        int maxPlayers = -1;
        Camera* currentCamera = NULL;
        std::vector<Ent*> controllers = std::vector<Ent*>();
    private:
        std::vector<Scene> scenes = std::vector<Scene>();
        int currentScene = 0;
        int nextScene = -1;

    public:
    
};

extern World world;
