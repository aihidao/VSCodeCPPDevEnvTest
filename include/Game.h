#ifndef __GAME__H__
#define __GAME__H__
#include <SDL.h>
#include "SDL_FontCache.h"
#include <SDL_image.h>
#include "TextRender.h"
#include "DebugInfoBox.h"

static int SCREEN_WIDTH = 800;
static int SCREEN_HEIGHT = 800;
class Game {
private:
    //The window we'll be rendering to
    SDL_Window* mWindow = NULL;

    //The window renderer
    SDL_Renderer* mRenderer = NULL;

    //TextRender
    //TextRender* mTextRender = NULL;

    DebugInfoBox* mDebugInfoBox = NULL;
    Text* testText = NULL;

public:

    bool start();
    //Starts up SDL and creates window
    bool init();

    //Loads media
    bool loadWidget();


    void update();

    void calculateFps();


    void updateDraw();

    //刷新事件函数
    Uint32 timerCallBack();

    //Frees media and shuts down SDL
    void close();
};
#endif
