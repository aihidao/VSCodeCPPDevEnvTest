#include "CellChunk.h"
#include "Game.h"
#include "GridCoordinateConverterUtils.h"
#include "iostream"
CellChunk::CellChunk(SDL_Renderer* renderer, TextRender *textRender, int startGridX, int startGridY, int width, int height, Cell** cellArray){
    this->mRenderer = renderer;
    this->mStartGridX = startGridX;
    this->mStartGridY = startGridY;
    this->mWidth = width;
    this->mHeight = height;
    this->mCellArray = cellArray;
    mTextRender = textRender;
    std::string positionInfo = "( " + std::to_string(startGridX) + "," + std::to_string(startGridY) + " )";
    //printf("init info:%s\n",positionInfo.c_str());
    mDebugInfo = new Text(positionInfo.c_str());

    //计算出最高的块，
    for(int i = 0; i < this->mWidth; i++){
        for(int j = 0; j < this->mHeight; j++){
            int index = (mStartGridY * Game::CHUNK_SIZE_HEIGHT + j) * Game::MAP_WIDTH + (mStartGridX * Game::CHUNK_SIZE_WIDTH + i);
            if(mCellArray[index]->getGroudAltitude() > this->mMaxAltitude){
                this->mMaxAltitude = mCellArray[index]->getGroudAltitude();
                SDL_Point pointTmp = GridCoordinateConverterUtils::convertToDraw({ i * Game::CELL_SIZE_WIDTH, j * Game::CELL_SIZE_HEIGHT});
                // if(this->mDrawMinY >  pointTmp.y - mCellArray[index]->getGroudAltitude()){
                //     this->mDrawMinY = pointTmp.y - mCellArray[index]->getGroudAltitude();
                // }
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

bool CellChunk::draw(){
    if(mTextureCreated == false){
        //创建一个线程去创建这个Texture
        createTexture();
        return false;
    }
    
    if(mChunkTexture != NULL){
        int posX = mStartGridX * Game::CHUNK_SIZE_WIDTH * Game::CELL_SIZE_WIDTH;
        int posY = mStartGridY * Game::CHUNK_SIZE_HEIGHT * Game::CELL_SIZE_HEIGHT;
        SDL_Point readPos = GridCoordinateConverterUtils::convertToDraw({posX, posY});

        int maxTextureWidth = this->mWidth * Game::CELL_SIZE_WIDTH;
        int maxTextureHeight = this->mHeight * Game::CELL_SIZE_HEIGHT;
        SDL_Point point0 = GridCoordinateConverterUtils::convertToDraw({0, 0});
        SDL_Point point1 = GridCoordinateConverterUtils::convertToDraw({maxTextureWidth, 0});
        SDL_Point point2 = GridCoordinateConverterUtils::convertToDraw({maxTextureWidth, maxTextureHeight});
        SDL_Point point3 = GridCoordinateConverterUtils::convertToDraw({0, maxTextureHeight});

        SDL_Point topLeftPoint = mCellArray[0]->getDrawPosition(Cell::OUTTER_RECT[0], true);
        SDL_Point topRightPoint = mCellArray[0]->getDrawPosition(Cell::OUTTER_RECT[1], true);
        SDL_Point bottomRightPoint = mCellArray[0]->getDrawPosition(Cell::OUTTER_RECT[2], true);
        SDL_Point bottomLeftPoint = mCellArray[0]->getDrawPosition(Cell::OUTTER_RECT[3], true);

        int terrainWidth = topRightPoint.x - bottomLeftPoint.x;

        SDL_Rect srcRect = { 0, 0, point1.x - point3.x, point2.y - point0.y  + this->mMaxAltitude};
        SDL_Rect dstRect = { static_cast<int>((GameStage::STAGE_POSITION_X + readPos.x - (point0.x - point3.x)) * GameStage::GAME_MAP_SCALE), static_cast<int>((GameStage::STAGE_POSITION_Y + readPos.y + this->mDrawMinY) * GameStage::GAME_MAP_SCALE), static_cast<int>((point1.x - point3.x) * GameStage::GAME_MAP_SCALE), static_cast<int>((point2.y - point0.y - this->mDrawMinY) * GameStage::GAME_MAP_SCALE)};
        //SDL_Rect dstRect = { (GameStage::STAGE_POSITION_X + readPos.x) * GameStage::GAME_MAP_SCALE, (GameStage::STAGE_POSITION_Y + readPos.y) * GameStage::GAME_MAP_SCALE, maxTextureWidth * GameStage::GAME_MAP_SCALE, maxTextureHeight * GameStage::GAME_MAP_SCALE};
        SDL_RenderCopy(mRenderer, mChunkTexture, &srcRect, &dstRect);
    }

    return true;
}

bool CellChunk::createTexture(){
    //Texture大小
    if(mChunkTexture == NULL){
        int maxTextureWidth = this->mWidth * Game::CELL_SIZE_WIDTH;
        int maxTextureHeight = this->mHeight * Game::CELL_SIZE_HEIGHT;
        SDL_Point point0 = GridCoordinateConverterUtils::convertToDraw({0, 0});
        SDL_Point point1 = GridCoordinateConverterUtils::convertToDraw({maxTextureWidth, 0});
        SDL_Point point2 = GridCoordinateConverterUtils::convertToDraw({maxTextureWidth, maxTextureHeight});
        SDL_Point point3 = GridCoordinateConverterUtils::convertToDraw({0, maxTextureHeight});

        mChunkTexture = SDL_CreateTexture(mRenderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, point1.x - point3.x, point2.y - point0.y - this->mDrawMinY);
        //mChunkTexture = SDL_CreateTexture(mRenderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, maxTextureWidth, maxTextureHeight);
        SDL_SetTextureBlendMode(mChunkTexture, SDL_BLENDMODE_BLEND);
    }

    mTextureCreated = updateTexture();
    // 清除渲染目标
    SDL_SetRenderTarget(mRenderer, NULL);
}

bool CellChunk::updateTexture(){
    int maxTextureWidth = this->mWidth * Game::CELL_SIZE_WIDTH;
    int maxTextureHeight = this->mHeight * Game::CELL_SIZE_HEIGHT;
    SDL_Point point0 = GridCoordinateConverterUtils::convertToDraw({0, 0});
    SDL_Point point1 = GridCoordinateConverterUtils::convertToDraw({maxTextureWidth, 0});
    SDL_Point point2 = GridCoordinateConverterUtils::convertToDraw({maxTextureWidth, maxTextureHeight});
    SDL_Point point3 = GridCoordinateConverterUtils::convertToDraw({0, maxTextureHeight});

    SDL_Point topLeftPoint = mCellArray[0]->getDrawPosition(Cell::OUTTER_RECT[0], true);
    SDL_Point topRightPoint = mCellArray[0]->getDrawPosition(Cell::OUTTER_RECT[1], true);
    SDL_Point bottomRightPoint = mCellArray[0]->getDrawPosition(Cell::OUTTER_RECT[2], true);
    SDL_Point bottomLeftPoint = mCellArray[0]->getDrawPosition(Cell::OUTTER_RECT[3], true);
    int createCount = 0;
    for(int i = 0; i < this->mWidth; i++){
        for(int j = 0; j < this->mHeight; j++){
            int index = (mStartGridY * Game::CHUNK_SIZE_HEIGHT + j) * Game::MAP_WIDTH + (mStartGridX * Game::CHUNK_SIZE_WIDTH + i);
            int gridX = mStartGridX * Game::CHUNK_SIZE_WIDTH + i;
            int gridY = mStartGridY * Game::CHUNK_SIZE_HEIGHT + j;
            //if(gridX < GameStage::BOTTOM_RIGHT_CELL_GRID_X && gridX >= GameStage::TOP_LEFT_CELL_GRID_X && gridY < GameStage::BOTTOM_RIGHT_CELL_GRID_Y && gridY >= GameStage::TOP_LEFT_CELL_GRID_Y){
                if(!mCellArray[index]->draw()){
                    ++createCount;
                    // 设置渲染目标为chunkTexture
                    SDL_SetRenderTarget(mRenderer, mChunkTexture);
                    int posX = i * Game::CELL_SIZE_WIDTH;
                    int posY = j * Game::CELL_SIZE_HEIGHT;

                    SDL_Point readPos = GridCoordinateConverterUtils::convertToDraw({posX, posY});
                    //SDL_Point srcPos = mCellArray[index]->getDrawPosition({0,0}, false);



                    int terrainWidth = topRightPoint.x - bottomLeftPoint.x;
                    int terrainHeight = bottomRightPoint.y - topLeftPoint.y  + mCellArray[index]->getGroudAltitude();

                    SDL_Rect srcRect = { 0, 0, terrainWidth, terrainHeight};
                    //SDL_Rect dstRect = {(readPos.x + (point0.x - point3.x - terrainWidth / 2)) , (readPos.y - this->mMaxAltitude - mCellArray[index]->getGroudAltitude()), terrainWidth , terrainHeight};
                    SDL_Rect dstRect = {(readPos.x + (point0.x - point3.x - terrainWidth / 2)) , (readPos.y - this->mDrawMinY - mCellArray[index]->getGroudAltitude()), terrainWidth , terrainHeight};
                    SDL_RenderCopy(mRenderer, mCellArray[index]->getTexture(), &srcRect, &dstRect);
                    mCellArray[index]->freeTexture();
                }
            //}
            if(createCount > 10){
                break;
            }
        }
        if(createCount > 10){
            break;
        }
    }

    if(createCount == 0){
        return true;
    }else{
        return false;
    }
}

bool CellChunk::drawDebugInfo(){
    int posX = mStartGridX * Game::CHUNK_SIZE_WIDTH * Game::CELL_SIZE_WIDTH;
    int posY = mStartGridY * Game::CHUNK_SIZE_HEIGHT * Game::CELL_SIZE_HEIGHT;
    SDL_Point readPos = GridCoordinateConverterUtils::convertToDraw({posX, posY});


    int maxTextureWidth = this->mWidth * Game::CELL_SIZE_WIDTH;
    int maxTextureHeight = this->mHeight * Game::CELL_SIZE_HEIGHT;
    SDL_Point point0 = GridCoordinateConverterUtils::convertToDraw({0, 0});
    SDL_Point point1 = GridCoordinateConverterUtils::convertToDraw({maxTextureWidth, 0});
    SDL_Point point2 = GridCoordinateConverterUtils::convertToDraw({maxTextureWidth, maxTextureHeight});
    SDL_Point point3 = GridCoordinateConverterUtils::convertToDraw({0, maxTextureHeight});

    SDL_Point topLeftPoint = mCellArray[0]->getDrawPosition(Cell::OUTTER_RECT[0], true);
    SDL_Point topRightPoint = mCellArray[0]->getDrawPosition(Cell::OUTTER_RECT[1], true);
    SDL_Point bottomRightPoint = mCellArray[0]->getDrawPosition(Cell::OUTTER_RECT[2], true);
    SDL_Point bottomLeftPoint = mCellArray[0]->getDrawPosition(Cell::OUTTER_RECT[3], true);

    int textureWidth = point1.x - point3.x;
    int textureHeight = point2.y - point0.y  - this->mDrawMinY;
    SDL_Rect dstRect = { static_cast<int>((GameStage::STAGE_POSITION_X + readPos.x - (point0.x - point3.x)) * GameStage::GAME_MAP_SCALE), static_cast<int>((GameStage::STAGE_POSITION_Y + readPos.y + this->mDrawMinY) * GameStage::GAME_MAP_SCALE), static_cast<int>((point1.x - point3.x) * GameStage::GAME_MAP_SCALE), static_cast<int>((point2.y - point0.y - this->mDrawMinY) * GameStage::GAME_MAP_SCALE)};

    int startX = dstRect.x;
    int startY = dstRect.y;
    int width = dstRect.w;
    int height = dstRect.h;
    SDL_SetRenderTarget(mRenderer, NULL);
    SDL_SetRenderDrawColor(mRenderer, 255, 0, 0, 255);
    SDL_RenderDrawLine(mRenderer, startX, startY, startX + width, startY);
    SDL_RenderDrawLine(mRenderer, startX, startY + 1, startX + width, startY + 1);

    SDL_RenderDrawLine(mRenderer, startX, startY, startX, startY + height);
    SDL_RenderDrawLine(mRenderer, startX + 1, startY, startX + 1, startY + height);

    SDL_SetRenderDrawColor(mRenderer, 0, 0, 0, 255);
    SDL_RenderDrawLine(mRenderer, startX + width, startY, startX + width, startY + height);
    SDL_RenderDrawLine(mRenderer, startX, startY + height, startX + width, startY + height);


    mTextRender->drawText(mDebugInfo,startX + 10, startY + mDebugInfo->getRect().h,TextRender::RENDER_TYPE_NOMAL);
}

CellChunk::~CellChunk(){
    if(mChunkTexture != NULL){
        SDL_DestroyTexture(mChunkTexture);
        mChunkTexture = NULL;
    }
    if(mDebugInfo != NULL){
        delete mDebugInfo;
        mDebugInfo = NULL;
    }
}