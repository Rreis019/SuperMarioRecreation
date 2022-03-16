#pragma once
#include <SDL2/SDL.h>
#include <vector>
#include <string>

class Sprite
{
    public:
        ~Sprite();
        Sprite(){}
        void draw(int x,int y,SDL_RendererFlip flip = SDL_FLIP_NONE);
        Sprite(const char* filename);
        Sprite(const char* filename,SDL_Color transparentColor);
        Sprite(SDL_Surface* image_surface, int w, int h,SDL_Color transparentColor);
        void destroy();
    private:
    public:
        SDL_Texture* texture = NULL;
        int w = 0,h = 0;
};

struct SpreadSheetInfo
{
    int width, height;
    SDL_Color transparent;
    int margin;
};

void loadSpriteSheet(std::vector<Sprite>& sprites,const char*  imagePath);
void loadMultipleImages(std::vector<Sprite>& sprites, std::string FolderPath, std::string Base_ImageName);//load all textures in folder

