#ifndef __CELL__
#define __CELL__
#include <SDL.h>
#include "Text.h"
#include "TextRender.h"
class Cell{
    public:
        Cell* leftCell = NULL;
        Cell* rightCell = NULL;
        Cell* upCell = NULL;
        Cell* downCell = NULL;
        // 1--->2
        // |   |
        //4<----3
        static SDL_Point OUTTER_RECT[4];
        static SDL_Point INNER_RECT[4];
    private:
        int mLocalX = 0;
        int mLocalY = 0;
        int mType = 0;
        int mAltitude = 0;
        //Text* mText = NULL;
        Text* mText = NULL;
        SDL_Renderer* mRenderer = NULL;
        TextRender *mTextRender = NULL;
        SDL_Texture* mCellTexture = NULL;
    public:
        Cell();
        Cell(SDL_Renderer* renderer,TextRender *textRender,int x,int y,int type);
        void setAltitude(int mAltitude);
        void draw();
        SDL_Texture* createCellTexture();
        void updateTexture();
        SDL_Texture* getTexture();
        void drawTerrain();
        void drawCellInfo();
        int getGroudAltitude();
        SDL_Point getDrawPosition(SDL_Point stagePosition,bool isWater);
        SDL_Point getDrawPositionWithAltitude(SDL_Point stagePosition,bool isWater);
        SDL_Point getDrawPositioniByCellRelativePosition(SDL_Point cellRelativePosition,bool isWater);
        SDL_Point getDrawPositioniByNearCellPosition(SDL_Point nearPosition,bool isWater);
        SDL_Color getGroudColor();
        void freeTexture();
        ~Cell();
};
#endif