#ifndef __PROGRESS_BAR_H_
#define __PROGRESS_BAR_H_
#include "SDL.h"
class ProgressBar{
    private:
        SDL_Renderer *mRenderer = NULL;
        SDL_Rect mRect;
    public:
        ProgressBar(SDL_Renderer* renderer,SDL_Rect rect);
        void draw(float rate);
        ~ProgressBar();
};
#endif