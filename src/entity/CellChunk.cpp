#include "CellChunk.h"
#include "Game.h"
CellChunk::CellChunk(SDL_Renderer* renderer, int startGridX, int startGridY, int width, int height, Cell** cellArray){
    this->mRenderer = renderer;
    this->mStartGridX = startGridX;
    this->mStartGridY = startGridY;
    this->mWidth = width;
    this->mHeight = height;
    this->mCellArray = cellArray;
}

int CellChunk::getStartGridX(){
    return this->mStartGridX;
}

int CellChunk::getStartGridY(){
    return this->mStartGridY;
}

int CellChunk::getWidth(){
    return this->mWidth;
}

int CellChunk::getHeight(){
    return this->mHeight;
}

void CellChunk::draw(){
    for(int i = 0; i < this->mWidth; i++){
        for(int j = 0; j < this->mHeight; j++){
            int index = (mStartGridY + j) * Game::MAP_WIDTH + (mStartGridX + i);
            // for (int y = GameStage::TOP_LEFT_CELL_GRID_Y; y < GameStage::BOTTOM_RIGHT_CELL_GRID_Y; y++) {
            // 	for (int x = GameStage::TOP_LEFT_CELL_GRID_X; x < GameStage::BOTTOM_RIGHT_CELL_GRID_X; x++) {
            // 		mCellArray[y * Game::MAP_WIDTH + x]->draw();
            // 	}
            // }
            int gridX = mStartGridX + i;
            int gridY = mStartGridY + j;
            if(gridX < GameStage::BOTTOM_RIGHT_CELL_GRID_X && gridX >= GameStage::TOP_LEFT_CELL_GRID_X && gridY < GameStage::BOTTOM_RIGHT_CELL_GRID_Y && gridY >= GameStage::TOP_LEFT_CELL_GRID_Y){
                mCellArray[index]->draw();
            }

        }
    }
}