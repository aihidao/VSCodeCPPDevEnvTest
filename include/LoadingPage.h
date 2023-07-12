#ifndef __LOADING_PAGE__
#define __LOADING_PAGE__
#include "SDL.h"
#include "TextRender.h"
#include "ProgressBar.h"
class LoadingPage{
    private:
        TextRender *mTextRender = NULL;
        SDL_Renderer *mRenderer = NULL;
        ProgressBar *mProgressBar = NULL;
        //loadingInfo
        Text* mLoadingInfo = NULL;
    public:
        LoadingPage(SDL_Renderer* renderer);
        bool handleEvent(SDL_Event* e);
        void draw();
        ~LoadingPage();
};
#endif