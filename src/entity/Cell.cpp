#include "Cell.h"

Cell::Cell(){
    mRenderer = NULL;
    mLocalX = 0;
    mLocalY = 0;
    mType = 0;
}

Cell::Cell(SDL_Renderer* renderer, TextRender *textRender,int x,int y,int type){
    mRenderer = renderer;
    mTextRender = textRender;
    mLocalX = x;
    mLocalY = y;
    mType = type;
}

void Cell::draw(){
    SDL_Rect rect = {mLocalX * 50,mLocalY * 50,50,50};
    SDL_SetRenderDrawColor(mRenderer,255,0,0,255);
    SDL_RenderDrawRect(mRenderer,&rect);
    SDL_SetRenderDrawColor(mRenderer,255,255,0,255);
    std::string positionInfo = "(" + std::to_string(mLocalX) + "," + std::to_string(mLocalY) + ")";
    mTextRender->drawText(positionInfo.c_str(),mLocalX * 50 + 10,mLocalY * 50 + 10);
}

Cell::~Cell(){
    //SDL_DestroyRenderer(mRenderer);
}