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
    //计算出最高的块，
    for(int i = 0; i < this->mWidth; i++){
        for(int j = 0; j < this->mHeight; j++){
            int index = (mStartGridY * Game::CHUNK_SIZE_HEIGHT + j) * Game::MAP_WIDTH + (mStartGridX * Game::CHUNK_SIZE_WIDTH + i);
            if(mCellArray[index]->getGroudAltitude() > this->mMaxAltitude){
                this->mMaxAltitude = mCellArray[index]->getGroudAltitude();
            }
        }
    }
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

        SDL_Rect srcRect = { 0, 0, point1.x - point3.x, point2.y - point0.y  + this->mMaxAltitude};
        SDL_Rect dstRect = { static_cast<int>((GameStage::STAGE_POSITION_X + readPos.x + (point0.x - point3.x)) * GameStage::GAME_MAP_SCALE), static_cast<int>((GameStage::STAGE_POSITION_Y + readPos.y - this->mMaxAltitude) * GameStage::GAME_MAP_SCALE), static_cast<int>((point1.x - point3.x) * GameStage::GAME_MAP_SCALE), static_cast<int>((point2.y - point0.y + this->mMaxAltitude) * GameStage::GAME_MAP_SCALE)};
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

    mChunkTexture = SDL_CreateTexture(mRenderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, point1.x - point3.x, point2.y - point0.y + this->mMaxAltitude);
    //mChunkTexture = SDL_CreateTexture(mRenderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, maxTextureWidth, maxTextureHeight);
    SDL_SetTextureBlendMode(mChunkTexture, SDL_BLENDMODE_BLEND);
    updateTexture();
    // 清除渲染目标
    SDL_SetRenderTarget(mRenderer, NULL);

}

void CellChunk::updateTexture(){
    int maxTextureWidth = this->mWidth * Game::CELL_SIZE_WIDTH;
    int maxTextureHeight = this->mHeight * Game::CELL_SIZE_HEIGHT;
    SDL_Point point0 = GridCoordinateConverterUtils::convertToDraw({0, 0});
    SDL_Point point1 = GridCoordinateConverterUtils::convertToDraw({maxTextureWidth, 0});
    SDL_Point point2 = GridCoordinateConverterUtils::convertToDraw({maxTextureWidth, maxTextureHeight});
    SDL_Point point3 = GridCoordinateConverterUtils::convertToDraw({0, maxTextureHeight});

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

                int terrainWidth = topRightPoint.x - bottomLeftPoint.x;
                int terrainHeight = bottomRightPoint.y - topLeftPoint.y  + mCellArray[index]->getGroudAltitude();


                SDL_Rect srcRect = { 0, 0, terrainWidth, terrainHeight};
                SDL_Rect dstRect = {(readPos.x + (point0.x - point3.x - terrainWidth / 2)) , (readPos.y + this->mMaxAltitude - mCellArray[index]->getGroudAltitude()), terrainWidth , terrainHeight};
                SDL_RenderCopy(mRenderer, mCellArray[index]->getTexture(), &srcRect, &dstRect);
                mCellArray[index]->freeTexture();
            //}
        }
    }

    // int textureWidth = point1.x - point3.x;
    // int textureHeight = point2.y - point0.y  + this->mMaxAltitude;
    // SDL_SetRenderTarget(mRenderer, mChunkTexture);
    // SDL_SetRenderDrawColor(mRenderer, 255, 0, 0, 255);
    // SDL_RenderDrawLine(mRenderer, 0, 0, textureWidth, 0);
    // SDL_RenderDrawLine(mRenderer, 0, 1, textureWidth, 1);
    // SDL_RenderDrawLine(mRenderer, 0, 2, textureWidth, 2);
    // SDL_RenderDrawLine(mRenderer, 0, 3, textureWidth, 3);
    // SDL_RenderDrawLine(mRenderer, 0, 4, textureWidth, 4);

    // SDL_RenderDrawLine(mRenderer, 0, 0, 0, textureHeight);
    // SDL_RenderDrawLine(mRenderer, 1, 0, 1, textureHeight);
    // SDL_RenderDrawLine(mRenderer, 2, 0, 2, textureHeight);
    // SDL_RenderDrawLine(mRenderer, 3, 0, 3, textureHeight);
    // SDL_RenderDrawLine(mRenderer, 4, 0, 4, textureHeight);

    // SDL_RenderDrawLine(mRenderer, textureWidth, 0, textureWidth, textureHeight);
    // SDL_RenderDrawLine(mRenderer, textureWidth - 1, 0, textureWidth - 1, textureHeight);
    // SDL_RenderDrawLine(mRenderer, textureWidth - 2, 0, textureWidth - 2, textureHeight);
    // SDL_RenderDrawLine(mRenderer, textureWidth - 3, 0, textureWidth - 3, textureHeight);
    // SDL_RenderDrawLine(mRenderer, textureWidth - 4, 0, textureWidth - 4, textureHeight);

    // SDL_RenderDrawLine(mRenderer, textureWidth - 5, 0, textureWidth - 5, textureHeight);
    // SDL_RenderDrawLine(mRenderer, textureWidth - 6, 0, textureWidth - 6, textureHeight);
    // SDL_RenderDrawLine(mRenderer, textureWidth - 7, 0, textureWidth - 7, textureHeight);
    // SDL_RenderDrawLine(mRenderer, textureWidth - 8, 0, textureWidth - 8, textureHeight);

    // SDL_RenderDrawLine(mRenderer, 0, textureHeight, textureWidth, textureHeight);
    // SDL_RenderDrawLine(mRenderer, 0, textureHeight - 1, textureWidth, textureHeight - 1);
    // SDL_RenderDrawLine(mRenderer, 0, textureHeight - 2, textureWidth, textureHeight - 2);
    // SDL_RenderDrawLine(mRenderer, 0, textureHeight - 3, textureWidth, textureHeight - 3);
    // SDL_RenderDrawLine(mRenderer, 0, textureHeight - 4, textureWidth, textureHeight - 4);

    // SDL_RenderDrawLine(mRenderer, 0, textureHeight - 5, textureWidth, textureHeight - 5);
    // SDL_RenderDrawLine(mRenderer, 0, textureHeight - 6, textureWidth, textureHeight - 6);
    // SDL_RenderDrawLine(mRenderer, 0, textureHeight - 7, textureWidth, textureHeight - 7);
    // SDL_RenderDrawLine(mRenderer, 0, textureHeight - 8, textureWidth, textureHeight - 8);

}