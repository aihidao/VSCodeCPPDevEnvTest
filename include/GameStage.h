#ifndef __GAMESTAGE_H__
#define __GAMESTAGE_H__
#include "TextRender.h"
#include "SDL.h"
#include "Cell.h"
#include "DebugInfoBox.h"
#include "Text.h"
#include "CellChunk.h"
class GameStage{
    public:
        static int STAGE_POSITION_X;
        static int STAGE_POSITION_Y;
        static double GAME_MAP_SCALE;
        static int STAGE_SHOW_LOCAL_X;
        static int STAGE_SHOW_LOCAL_Y;

        static int SELECT_LOCAL_X;
        static int SELECT_LOCAL_Y;

        static int TOP_LEFT_CELL_GRID_X;
        static int TOP_LEFT_CELL_GRID_Y;

        static int BOTTOM_RIGHT_CELL_GRID_X;
        static int BOTTOM_RIGHT_CELL_GRID_Y;

        bool mIsMove = false;
        int mDownMovePositionX = 0;
        int mDownMovePositionY = 0;
    private:
        TextRender *mTextRender = NULL;
        SDL_Renderer *mRenderer = NULL;
        Cell** mCellArray = NULL;
        CellChunk** mCellChunkArray = NULL;
        int mCellChunkArrayWidth = 0;
        int mCellChunkArrayHeight = 0;
        DebugInfoBox* mDebugInfoBox = NULL;
        //fps
        int frameCount = 0;
        Uint32 frameStart;
        Text* mFpsText = NULL;
        //mouse position
        int mMouseX = 0;
        int mMouseY = 0;
        int mMouseSelectX = 0;
        int mMouseSelectY = 0;
        Text* mMousePosition = NULL;
        Text* mMouseSelectPos = NULL;
        Text* mStagePosition = NULL;
        Text* mStageShow = NULL;
    public:
        GameStage(SDL_Renderer* renderer);
        void initGrid();
        void getShowGridInfo();
        bool handleEvent(SDL_Event* e);
        void calculateFps();
        void mouseDown(SDL_Event *e);
        void mouseMove(SDL_Event* e);
        void mouseUp(SDL_Event* e);
        void draw();
        ~GameStage();
};
#endif