#include "LoadingPage.h"
#include "Game.h"
LoadingPage::LoadingPage(SDL_Renderer* renderer){
    this->mRenderer = renderer;
    this->mTextRender = new TextRender(renderer, 15, {0, 0, 0, 255});
    mLoadingInfo = new Text("Loading...");
    mProgressBar = new ProgressBar(renderer,{200,200,500,50});
}

bool LoadingPage::handleEvent(SDL_Event* e){
    bool quit = false;
    while (SDL_PollEvent(e) != 0)
    {
        if (e->type == SDL_QUIT) {
            quit = true;
        }
    }
    return quit;
}

void LoadingPage::draw(){
    SDL_SetRenderDrawColor(mRenderer, 125, 125, 125, 0xFF);
    //Clear screen
    SDL_RenderClear(mRenderer);
    float rate = (Game::initProgress) * 1.0f / (Game::MAP_WIDTH * Game::MAP_HEIGHT);
    // int fullCount = 500;
    // int progressCount = fullCount * ((Game::initProgress) * 1.0f / (Game::MAP_WIDTH * Game::MAP_HEIGHT));
    // SDL_Rect rect = {200,200, progressCount, 50};
    // SDL_SetRenderDrawColor(mRenderer, 0, 0, 255, 0xFF);
    // SDL_RenderFillRect(mRenderer, &rect);
    // SDL_SetRenderDrawColor(mRenderer, 0, 0, 0, 0xFF);
    // SDL_Rect rectFill = {200,200, fullCount, 50};
    // SDL_RenderDrawRect(mRenderer, &rectFill);
    mProgressBar->draw(rate);
    mLoadingInfo->setStr("Need loading:" + std::to_string(Game::initProgress) + "/" + std::to_string(Game::MAP_WIDTH * Game::MAP_HEIGHT));
    mTextRender->drawString(mLoadingInfo->getStr(),100,100);

    //Update screen
	SDL_RenderPresent(mRenderer);

}

LoadingPage::~LoadingPage(){
    delete mLoadingInfo;
    delete mProgressBar;
}