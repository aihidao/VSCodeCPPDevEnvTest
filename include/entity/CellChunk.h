#ifndef __CELL_CHUNK__H__
#define __CELL_CHUNK__H__
#include "SDL.h"
#include "Cell.h"
class CellChunk{
    public:
        CellChunk* leftCellChunk = NULL;
        CellChunk* rightCellChunk = NULL;
        CellChunk* upCellChunk = NULL;
        CellChunk* downCellChunk = NULL;
    private:
        int startGridX;
        int startGridY;
        int mWidth;
        int mHeight;

        Cell** mCellArray = NULL;

        SDL_Renderer *mRenderer = NULL;
    public:
        CellChunk(SDL_Renderer* renderer, int startGridX, int startGridY, int width, int height, Cell** cellArray);
        int getStartGridX();
        int getStartGridY();
        int getWidth();
        int getHeight();
        ~CellChunk();
};
#endif