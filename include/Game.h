#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <SDL2/SDL_ttf.h>

extern SDL_Renderer* renderer;
extern SDL_Window* window ;

class Game
{
    public:
        SDL_Color backgroundColor = {0, 0, 0, 255};
        int witdh, height;
        bool isRunning = true;
        bool isPaused = false;
        bool isFullscreen = false;
        int scale = 1;

        bool init();//init SDL and create window
        void loop();//main loop
        void setScale(int scale);
        void setFullscreen(bool fullscreen);
        void events();
        void render();
    private:
};

extern Game game;




