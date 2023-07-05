#ifndef __TEXT_RENDER__H__
#define __TEXT_RENDER__H__
#include <SDL.h>
#include "SDL_FontCache.h"
#include <string>
class TextRender {
private:
    SDL_Renderer* mRenderer = NULL;
    FC_Font* mFont = NULL;
    SDL_Color mFontColor = {255,0,0,255};
public:
    TextRender(SDL_Renderer* renderer);
    void loadAssets();
    void loadAssets(int fontSize);
    void drawText(std::string str,int x, int y);
    ~TextRender();
};

#endif