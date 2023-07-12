#include "ProgressBar.h"

ProgressBar::ProgressBar(SDL_Renderer* renderer,SDL_Rect rect){
    this->mRenderer = renderer;
    this->mRect = rect;
}

void ProgressBar::draw(float rate){
    int completeCount = mRect.w * rate;
    SDL_SetRenderDrawColor(mRenderer, 0, 0, 255, 0xFF);
    SDL_Rect rectFill = {200,200, completeCount, 50};
    SDL_RenderFillRect(mRenderer, &rectFill);
    SDL_SetRenderDrawColor(mRenderer, 0, 0, 0, 0xFF);
    SDL_RenderDrawRect(mRenderer, &mRect);
}

ProgressBar::~ProgressBar(){
    
}