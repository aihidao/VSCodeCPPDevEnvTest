#ifndef __GAMESTAGE_H__
#define __GAMESTAGE_H__
#include "TextRender.h"
#include "SDL.h"
#include "Cell.h"
class GameStage{
    public:
        static int STAGE_POSITION_X;
        static int STAGE_POSITION_Y;

        bool mIsMove = false;
        int mDownMovePositionX = 0;
        int mDownMovePositionY = 0;
    private:
        TextRender *mTextRender = NULL;
        SDL_Renderer *mRenderer = NULL;
        Cell** mCellArray = NULL;
    public:
        GameStage(SDL_Renderer* renderer);
        void handleEvent(SDL_Event* e);
        void mouseDown(SDL_Event *e);
        void mouseMove(SDL_Event* e);
        void mouseUp(SDL_Event* e);
        void draw();
        ~GameStage();
};
#endif