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

    static volatile int initProgress;
private:
    //The window we'll be rendering to
    SDL_Window* mWindow = NULL;
    //The window renderer
    SDL_Renderer* mRenderer = NULL;

    //SDL_Renderer* mLoadinigRenderer = NULL;

    //TextRender
    TextRender* mTextRender = NULL;

    bool mNeedLoading = true;
    LoadingPage* mLloadingPage = NULL;

    SDL_Thread* mLoadingThread = NULL;
    DebugInfoBox* mDebugInfoBox = NULL;
    //fps
    int frameCount = 0;
    Uint32 frameStart;
    Text* mFpsText = NULL;
    //mouse position
    int mMouseX = 0;
    int mMouseY = 0;
    int mMouseSelectX = 0;
    int mMouseSelectY = 0;
    Text* mMousePosition = NULL;
    Text* mMouseSelectPos = NULL;
    Text* mStagePosition = NULL;
    Text* mStageShow = NULL;

    GameStage* mGameStage = NULL;

public:

    Game();

    bool start();
    //Starts up SDL and creates window
    bool init();

    //Loads media
    bool initGameStage();

    bool calculateGameDate();

    bool handleEvent(SDL_Event* e);

    void update();

    void calculateFps();

    void updateDraw();
    //刷新事件函数
    Uint32 timerCallBack();
    //Frees media and shuts down SDL
    void close();
};
#endif
