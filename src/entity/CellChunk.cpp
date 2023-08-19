#include "CellChunk.h"
#include "Game.h"
#include "GridCoordinateConverterUtils.h"
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
    if(mChunkTexture == NULL){
        createTexture();
    }else{
        int posX = mStartGridX * Game::CHUNK_SIZE_WIDTH * Game::CELL_SIZE_WIDTH;
        int posY = mStartGridY * Game::CHUNK_SIZE_HEIGHT * Game::CELL_SIZE_HEIGHT;
        SDL_Point readPos = GridCoordinateConverterUtils::convertToDraw({posX, posY});

        int maxTextureWidth = this->mWidth * Game::CELL_SIZE_WIDTH;
        int maxTextureHeight = this->mHeight * Game::CELL_SIZE_HEIGHT;
        SDL_Point point0 = GridCoordinateConverterUtils::convertToDraw({0, 0});
        SDL_Point point1 = GridCoordinateConverterUtils::convertToDraw({maxTextureWidth, 0});
        SDL_Point point2 = GridCoordinateConverterUtils::convertToDraw({maxTextureWidth, maxTextureHeight});
        SDL_Point point3 = GridCoordinateConverterUtils::convertToDraw({0, maxTextureHeight});

        SDL_Rect srcRect = { 0, 0, point1.x - point3.x, point2.y - point0.y};
        SDL_Rect dstRect = { (GameStage::STAGE_POSITION_X + readPos.x) * GameStage::GAME_MAP_SCALE, (GameStage::STAGE_POSITION_Y + readPos.y) * GameStage::GAME_MAP_SCALE, (point1.x - point3.x) * GameStage::GAME_MAP_SCALE, (point2.y - point0.y) * GameStage::GAME_MAP_SCALE};
        //SDL_Rect dstRect = { (GameStage::STAGE_POSITION_X + readPos.x) * GameStage::GAME_MAP_SCALE, (GameStage::STAGE_POSITION_Y + readPos.y) * GameStage::GAME_MAP_SCALE, maxTextureWidth * GameStage::GAME_MAP_SCALE, maxTextureHeight * GameStage::GAME_MAP_SCALE};
        SDL_RenderCopy(mRenderer, mChunkTexture, &srcRect, &dstRect);
    }
}

SDL_Texture* CellChunk::createTexture(){
    //Texture大小
    int maxTextureWidth = this->mWidth * Game::CELL_SIZE_WIDTH;
    int maxTextureHeight = this->mHeight * Game::CELL_SIZE_HEIGHT;
    SDL_Point point0 = GridCoordinateConverterUtils::convertToDraw({0, 0});
    SDL_Point point1 = GridCoordinateConverterUtils::convertToDraw({maxTextureWidth, 0});
    SDL_Point point2 = GridCoordinateConverterUtils::convertToDraw({maxTextureWidth, maxTextureHeight});
    SDL_Point point3 = GridCoordinateConverterUtils::convertToDraw({0, maxTextureHeight});

    mChunkTexture = SDL_CreateTexture(mRenderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, point1.x - point3.x, point2.y - point0.y);
    //mChunkTexture = SDL_CreateTexture(mRenderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, maxTextureWidth, maxTextureHeight);
    SDL_SetTextureBlendMode(mChunkTexture, SDL_BLENDMODE_BLEND);
    updateTexture();
    // 清除渲染目标
    SDL_SetRenderTarget(mRenderer, NULL);

}

void CellChunk::updateTexture(){
    for(int i = 0; i < this->mWidth; i++){
        for(int j = 0; j < this->mHeight; j++){
            int index = (mStartGridY * Game::CHUNK_SIZE_HEIGHT + j) * Game::MAP_WIDTH + (mStartGridX * Game::CHUNK_SIZE_WIDTH + i);
            int gridX = mStartGridX * Game::CHUNK_SIZE_WIDTH + i;
            int gridY = mStartGridY * Game::CHUNK_SIZE_HEIGHT + j;
            //if(gridX < GameStage::BOTTOM_RIGHT_CELL_GRID_X && gridX >= GameStage::TOP_LEFT_CELL_GRID_X && gridY < GameStage::BOTTOM_RIGHT_CELL_GRID_Y && gridY >= GameStage::TOP_LEFT_CELL_GRID_Y){
                mCellArray[index]->draw();
                // 设置渲染目标为chunkTexture
                SDL_SetRenderTarget(mRenderer, mChunkTexture);
                int posX = i * Game::CELL_SIZE_WIDTH;
                int posY = j * Game::CELL_SIZE_HEIGHT;

                SDL_Point readPos = GridCoordinateConverterUtils::convertToDraw({posX, posY});
                //SDL_Point srcPos = mCellArray[index]->getDrawPosition({0,0}, false);
                SDL_Point topLeftPoint = mCellArray[index]->getDrawPosition(Cell::OUTTER_RECT[0], true);
                SDL_Point topRightPoint = mCellArray[index]->getDrawPosition(Cell::OUTTER_RECT[1], true);
                SDL_Point bottomRightPoint = mCellArray[index]->getDrawPosition(Cell::OUTTER_RECT[2], true);
                SDL_Point bottomLeftPoint = mCellArray[index]->getDrawPosition(Cell::OUTTER_RECT[3], true);

                int terrainWidht = topRightPoint.x - bottomLeftPoint.x;
                int terrainHeight = bottomRightPoint.y - topLeftPoint.y  + mCellArray[index]->getGroudAltitude();

                int maxTextureWidth = this->mWidth * Game::CELL_SIZE_WIDTH;
                int maxTextureHeight = this->mHeight * Game::CELL_SIZE_HEIGHT;
                SDL_Point point0 = GridCoordinateConverterUtils::convertToDraw({0, 0});
                SDL_Point point1 = GridCoordinateConverterUtils::convertToDraw({maxTextureWidth, 0});
                SDL_Point point2 = GridCoordinateConverterUtils::convertToDraw({maxTextureWidth, maxTextureHeight});
                SDL_Point point3 = GridCoordinateConverterUtils::convertToDraw({0, maxTextureHeight});

                SDL_Rect srcRect = { 0, 0, terrainWidht, terrainHeight};
                SDL_Rect dstRect = {(readPos.x + (point1.x - point3.x) / 2) , (readPos.y), terrainWidht , terrainHeight};
                SDL_RenderCopy(mRenderer, mCellArray[index]->getTexture(), &srcRect, &dstRect);
            //}
        }
    }
}