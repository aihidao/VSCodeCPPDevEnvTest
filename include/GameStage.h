#ifndef __GAMESTAGE_H__
#define __GAMESTAGE_H__
#include "TextRender.h"
#include "SDL.h"
#include "Cell.h"
class GameStage{
    private:
        TextRender *mTextRender = NULL;
        SDL_Renderer *mRenderer = NULL;
        Cell** mCellArray = NULL;
    public:
        GameStage(SDL_Renderer* renderer);
        void draw();
        ~GameStage();
};
#endif