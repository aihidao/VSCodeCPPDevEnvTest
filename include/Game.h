#pragma once
#include <SDL.h>
#include "SDL_FontCache.h"
#include <SDL_image.h>

static int SCREEN_WIDTH = 800;
static int SCREEN_HEIGHT = 800;
class Game {
private:
    //The window we'll be rendering to
    SDL_Window* mWindow = NULL;

    //The window renderer
    SDL_Renderer* mRenderer = NULL;

    //TTF_Font* font = NULL;
    FC_Font* font = NULL;

    int frameCount = 0;

public:

    bool start();
    //Starts up SDL and creates window
    bool init();

    //Loads media
    bool loadMedias();


    void update();

    void calculateFps();


    void updateDraw();

    //刷新事件函数
    Uint32 timerCallBack();

    //Frees media and shuts down SDL
    void close();
};
