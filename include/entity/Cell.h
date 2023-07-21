#ifndef __CELL__
#define __CELL__
#include <SDL.h>
#include "Text.h"
#include "TextRender.h"
class Cell{
    private:
        int mLocalX = 0;
        int mLocalY = 0;
        int mType = 0;
        int altitude = 0;
        //Text* mText = NULL;
        Text* mText = NULL;
        SDL_Renderer* mRenderer = NULL;
        TextRender *mTextRender = NULL;
    public:
        Cell();
        Cell(SDL_Renderer* renderer,TextRender *textRender,int x,int y,int type);
        void draw();
        void drawCellInfo();
        SDL_Color getGroudColor(double altitude);
        ~Cell();
};
#endif