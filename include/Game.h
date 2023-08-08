#ifndef __GAME__H__
#define __GAME__H__
#include <SDL.h>
#include "SDL_FontCache.h"
#include <SDL_image.h>
#include "TextRender.h"
#include "LoadingPage.h"
#include "DebugInfoBox.h"
#include "GameStage.h"
#include <atomic>
class Game {
public:
    static int SCREEN_WIDTH;
    static int SCREEN_HEIGHT;

    static int MAP_WIDTH;
    static int MAP_HEIGHT;

    static int CELL_SIZE_WIDTH;
    static int CELL_SIZE_HEIGHT;

    static int CHUNK_SIZE_WIDTH;
    static int CHUNK_SIZE_HEIGHT;

    static volatile int initProgress;
private:
    //The window we'll be rendering to
    SDL_Window* mWindow = NULL;
    //The window renderer
    SDL_Renderer* mRenderer = NULL;

    //SDL_Renderer* mLoadinigRenderer = NULL;

    //TextRender
    //TextRender* mTextRender = NULL;

    bool mNeedLoading = true;
    LoadingPage* mLoadingPage = NULL;
    SDL_Thread* mLoadingThread = NULL;

    GameStage* mGameStage = NULL;

public:

    Game();

    bool start();
    //Starts up SDL and creates window
    bool init();
    //Loads media
    bool initGameEnv();

    bool calculateGameDate();

    //bool handleEvent(SDL_Event* e);

    void update();

    //void updateDraw();
    //刷新事件函数
    Uint32 timerCallBack();
    //Frees media and shuts down SDL
    void close();
};
#endif
