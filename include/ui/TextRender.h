#ifndef __TEXT_RENDER__H__
#define __TEXT_RENDER__H__
#include <SDL.h>
#include "SDL_FontCache.h"
#include <string>
#include "Text.h"
class TextRender {
public:
    static const int RENDER_TYPE_NOMAL = 0;
    static const int RENDER_TYPE_W_CENTER = 1;
    static const int RENDER_TYPE_H_CENTER = 2;
    static const int RENDER_TYPE_CENTER = 3;
private:
    SDL_Renderer* mRenderer = NULL;
    FC_Font* mFont = NULL;
    SDL_Color mFontColor = {255,0,0,255};
public:
    TextRender(SDL_Renderer* renderer);
    void loadAssets();
    void loadAssets(int fontSize,SDL_Color fontColor);
    void drawText(Text* text,int x, int y, int renderMode);
    void drawString(std::string str,int x, int y);
    ~TextRender();
};

#endif