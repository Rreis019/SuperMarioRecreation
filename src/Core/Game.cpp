#include "ScreenManager.h"
#include "Game.h"
#include "Timer.h"
#include <stdio.h>
#include <windows.h>
#include "CustomFont.h"
#include "Hud.h"
#include "World.h"
#include "Input.h"
#include "Particle.h"
#include "SoundManager.h"
#include "Logger.h"
#include "ScoreSave.h"

#define WINDOW_WITDH 384 // 384 * 5 = 1920
#define WINDOW_HEIGHT 224// 216 * 5 = 1080
#define GAME_TITLE "Super mario made by :  Rodrigo Reis"

Game game;
SDL_Renderer* renderer;
SDL_Window* window ;

bool Game::init()
{
    initLogger();

    if(SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        log("SDL_Init Error: %s\n", SDL_GetError());
        return false;
    }

    window = SDL_CreateWindow(GAME_TITLE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WITDH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);


    if(window == NULL)
    {
        log("SDL_CreateWindow Error: %s\n", SDL_GetError());
        return false;
    }

    renderer = SDL_CreateRenderer(window,-1, SDL_RENDERER_ACCELERATED);
    if(renderer == NULL)
    {
        log("SDL_CreateRenderer(SDL_RENDERER_ACCELERATED) Error: %s\n", SDL_GetError());
        renderer = SDL_CreateRenderer(window,-1, SDL_RENDERER_SOFTWARE);
        if(renderer == NULL)
        {
            log("SDL_CreateRenderer(SDL_RENDERER_SOFTWARE) Error: %s\n", SDL_GetError());
            getchar();
            exit(1);
            return false;
        }
    }
    game.witdh = WINDOW_WITDH;
    game.height = WINDOW_HEIGHT;

    return true;
}


void Game::events()
{
    SDL_Event event;
    inputReset();
    while(SDL_PollEvent(&event))
    {
        switch(event.type)
        {            case SDL_QUIT:
                isRunning = false;
                break;
        }
        screenManager.getCurrentScreen()->events(event);
        inputEvents(event);
    }
}

void Game::render()
{
    SDL_SetRenderDrawColor(renderer, game.backgroundColor.r, game.backgroundColor.g, game.backgroundColor.b, game.backgroundColor.a);
    SDL_RenderClear(renderer); 
    screenManager.getCurrentScreen()->render();    //Render current screen
    SDL_RenderPresent(renderer);
}

void Game::loop()
{
    defaultFont = CustomFont("0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ*!.-x& ", "Resources/Fonts/HudFont.png", 8, 8);
    SDL_RenderSetLogicalSize(renderer, WINDOW_WITDH, WINDOW_HEIGHT);
    setScale(3);
    scoreSave.init();
    screenManager.init();
    particleSystem.init();
    soundManager.init();
    hud.init();
    world.init();
    screenManager.getCurrentScreen()->onChangeScene();
    while (isRunning)   
    {
        timer.tick(60);
        events();
        render();
        screenManager.updateChanges();
    }
    
    soundManager.destroy();
}


void Game::setScale(int scale)
{
    if(this->isFullscreen)
        setFullscreen(false);
        
    SDL_SetWindowSize(window, WINDOW_WITDH * scale, WINDOW_HEIGHT * scale);
    this->scale = scale;
    SDL_SetWindowPosition(window, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
}

void Game::setFullscreen(bool fullscreen)
{
    if(fullscreen)
    {
        SDL_DisplayMode dm;
        SDL_GetCurrentDisplayMode(0, &dm);
        SDL_SetWindowSize(window, dm.w, dm.h);

        SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN);
        this->isFullscreen = true;
    }
    else
    {
        SDL_SetWindowFullscreen(window, 0);
        setScale(this->scale);
        this->isFullscreen = false;
    }
}