#ifndef __LOADING_PAGE__
#define __LOADING_PAGE__
#include "SDL.h"
#include "TextRender.h"
class LoadingPage{
    private:
        TextRender *mTextRender = NULL;
        SDL_Renderer *mRenderer = NULL;
            //loadingInfo
        Text* mLoadingInfo = NULL;
    public:
        LoadingPage(SDL_Renderer* renderer);
        bool handleEvent(SDL_Event* e);
        void draw();
        ~LoadingPage();
};
#endif