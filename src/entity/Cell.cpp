#include "Cell.h"
#include "Game.h"
#include <cmath>
#include "MapGenerator.h"
#include "GameStage.h"
#include "GridCoordinateConverterUtils.h"
#include "DrawUtils.h"
// ---->
// |   |
// <----
SDL_Point Cell::OUTTER_RECT[4] = { 
    {0, 0}, 
    {Game::CELL_SIZE_WIDTH , 0}, 
    {Game::CELL_SIZE_WIDTH, Game::CELL_SIZE_HEIGHT}, 
    {0, Game::CELL_SIZE_HEIGHT} 
};

// SDL_Point Cell::INNER_RECT[4] = { 
//     {Game::CELL_SIZE_WIDTH / 4, Game::CELL_SIZE_HEIGHT / 4}, 
//     {3 * Game::CELL_SIZE_WIDTH / 4 , Game::CELL_SIZE_HEIGHT / 4}, 
//     {3 * Game::CELL_SIZE_WIDTH / 4, 3 * Game::CELL_SIZE_HEIGHT / 4}, 
//     {Game::CELL_SIZE_WIDTH / 4, 3 * Game::CELL_SIZE_HEIGHT / 4} 
// };

SDL_Point Cell::INNER_RECT[4] = { 
    {Game::CELL_SIZE_WIDTH / 2, Game::CELL_SIZE_HEIGHT / 2}, 
    {Game::CELL_SIZE_WIDTH / 2, Game::CELL_SIZE_HEIGHT / 2}, 
    {Game::CELL_SIZE_WIDTH / 2, Game::CELL_SIZE_HEIGHT / 2}, 
    {Game::CELL_SIZE_WIDTH / 2, Game::CELL_SIZE_HEIGHT / 2} 
};

Cell::Cell(){
    mRenderer = NULL;
    mLocalX = 0;
    mLocalY = 0;
    mType = 0;
    mText = new Text("UNDEFINED");
}

Cell::Cell(SDL_Renderer* renderer, TextRender *textRender, int x, int y, int type){
    mRenderer = renderer;
    mTextRender = textRender;
    mLocalX = x;
    mLocalY = y;
    mType = type;
    double scale = 0.05;
    //printf("noise:%f\n",MapGererator::perlinNoise(x * scale, y * scale, 0.0));
    //mAltitude = std::round(MapGererator::perlinNoise(x * scale,  y * scale, 0.0) * 200.0) - 100;
    // printf("noise:%f\n",MapGererator::perlinNoise(x * scale, y * scale, 0.0));
    // printf("noise:%d\n", mAltitude);
    //std::string positionInfo = "(" + std::to_string(mLocalX) + "," + std::to_string(mLocalY) + "," + std::to_string(mAltitude) + ")";
    std::string positionInfo = "( undefine )";
    //printf("init info:%s\n",positionInfo.c_str());
    mText = new Text(positionInfo.c_str());
    //mText->setStr(positionInfo);
}

void Cell::setAltitude(int altitude){
    mAltitude = altitude;
    std::string positionInfo = "(" + std::to_string(mAltitude) + ")";
    mText->setStr(positionInfo);
}

bool Cell::draw(){
    if(mCellTexture == NULL){
        //mCellTexture = SDL_CreateTexture(mRenderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, Game::CELL_SIZE_WIDTH, Game::CELL_SIZE_HEIGHT);
        createCellTexture();
        return false;
    }else{

    }
    return true;
}

bool Cell::createCellTexture(){
    SDL_Point topLeftPoint = getDrawPosition(Cell::OUTTER_RECT[0], false);
    SDL_Point topRightPoint = getDrawPosition(Cell::OUTTER_RECT[1], false);
    SDL_Point bottomRightPoint = getDrawPosition(Cell::OUTTER_RECT[2], false);
    SDL_Point bottomLeftPoint = getDrawPosition(Cell::OUTTER_RECT[3], false);

    int groudAltitude = mAltitude > 0 ? mAltitude : 0;
    int terrainWidht = topRightPoint.x - bottomLeftPoint.x;
    int terrainHeight = bottomRightPoint.y - topLeftPoint.y + groudAltitude;
    // 创建一个目标纹理
    mCellTexture = SDL_CreateTexture(mRenderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET,  terrainWidht, terrainHeight);
    SDL_SetTextureBlendMode(mCellTexture, SDL_BLENDMODE_BLEND);
    // 设置渲染目标为chunkTexture
    SDL_SetRenderTarget(mRenderer, mCellTexture);

    updateTexture();
    
    // 清除渲染目标
    SDL_SetRenderTarget(mRenderer, NULL);
    mTextureCreated = true;
    return mTextureCreated;
}

SDL_Texture* Cell::getTexture(){
    return mCellTexture;
}

void Cell::updateTexture(){
    SDL_Color groudColor = getGroudColor();
    SDL_Color colors[] = {
        groudColor,
        groudColor,
        groudColor,
        groudColor
        //leftCell->getGroudColor()
    };

    SDL_Point topLeftPoint = getDrawPosition(Cell::OUTTER_RECT[0], false);
    SDL_Point topRightPoint = getDrawPosition(Cell::OUTTER_RECT[1], false);
    SDL_Point bottomRightPoint = getDrawPosition(Cell::OUTTER_RECT[2], false);
    SDL_Point bottomLeftPoint = getDrawPosition(Cell::OUTTER_RECT[3], false);
    int terrainWidht = topRightPoint.x - bottomLeftPoint.x;
    int terrainHeight = bottomRightPoint.y - topLeftPoint.y;

    SDL_Point points[] = {
        {topLeftPoint.x + terrainWidht / 2, topLeftPoint.y},
        {topRightPoint.x + terrainWidht / 2, topRightPoint.y},
        {bottomRightPoint.x + terrainWidht / 2, bottomRightPoint.y},
        {bottomLeftPoint.x + terrainWidht / 2, bottomLeftPoint.y},
    };

    DrawUtils::drawQuadrilateral(mRenderer, points, colors);

    //连接下一个cell
    if(downCell != NULL){
        if(mAltitude > downCell->mAltitude){
            SDL_Point p1 = this->getDrawPosition(Cell::OUTTER_RECT[2], false);
            SDL_Point p2 = this->getDrawPosition(Cell::OUTTER_RECT[3], false);
            SDL_Point pointsAdjust[] = {
                {p1.x + terrainWidht / 2 , p1.y},
                {p2.x + terrainWidht / 2 , p2.y},
                {p2.x + terrainWidht / 2 , p2.y + getGroudAltitude() - downCell->getGroudAltitude()},
                {p1.x + terrainWidht / 2 , p1.y + getGroudAltitude() - downCell->getGroudAltitude()}
            };

            SDL_Color colorsAdjust[] = {
                groudColor, 
                groudColor,
                downCell->getGroudColor(),
                downCell->getGroudColor()
            };

            // SDL_Color colorsAdjust[] = {
            //     {255,0,0,255},
            //     {255,0,0,255},
            //     {255,0,0,255},
            //     {255,0,0,255}
            // };

            DrawUtils::drawQuadrilateral(mRenderer, pointsAdjust, colorsAdjust);
        }
    }

    if(rightCell != NULL){
        if(mAltitude > rightCell->mAltitude){
            SDL_Point p1 = this->getDrawPosition(Cell::OUTTER_RECT[1], false);
            SDL_Point p2 = this->getDrawPosition(Cell::OUTTER_RECT[2], false);
            SDL_Point pointsAdjust[] = {
                {p1.x + terrainWidht / 2 , p1.y},
                {p2.x + terrainWidht / 2 , p2.y},
                {p2.x + terrainWidht / 2 , p2.y + getGroudAltitude() - rightCell->getGroudAltitude()},
                {p1.x + terrainWidht / 2 , p1.y + getGroudAltitude() - rightCell->getGroudAltitude()}
            };

            SDL_Color colorsAdjust[] = {
                groudColor,
                groudColor,
                rightCell->getGroudColor(),
                rightCell->getGroudColor()
                //leftCell->getGroudColor()
            };

            // SDL_Color colorsAdjust[] = {
            //     {255,0,0,255},
            //     {255,0,0,255},
            //     {255,0,0,255},
            //     {255,0,0,255}
            // };

            DrawUtils::drawQuadrilateral(mRenderer, pointsAdjust, colorsAdjust);
        }
    }
}

void Cell::drawTerrain(){
    SDL_Color groudColor = getGroudColor();

    SDL_Color colors[] = {
        groudColor,
        groudColor,
        groudColor,
        groudColor
        //leftCell->getGroudColor()
    };

    SDL_Point points[] = {
        this->getDrawPositioniByCellRelativePosition(Cell::OUTTER_RECT[0], false),
        this->getDrawPositioniByCellRelativePosition(Cell::OUTTER_RECT[1], false),
        this->getDrawPositioniByCellRelativePosition(Cell::OUTTER_RECT[2], false),
        this->getDrawPositioniByCellRelativePosition(Cell::OUTTER_RECT[3], false)
    };
    DrawUtils::drawQuadrilateral(mRenderer, points, colors);

    if(leftCell != NULL){
        if(mAltitude < leftCell->mAltitude){
            SDL_Point pointsAdjust[] = {
                this->getDrawPositioniByCellRelativePosition(Cell::OUTTER_RECT[0], false),
                this->getDrawPositioniByCellRelativePosition(Cell::OUTTER_RECT[3], false),
                leftCell->getDrawPositioniByCellRelativePosition(Cell::OUTTER_RECT[2], false),
                leftCell->getDrawPositioniByCellRelativePosition(Cell::OUTTER_RECT[1], false)
            };

            SDL_Color colorsAdjust[] = {
                groudColor,
                groudColor,
                leftCell->getGroudColor(),
                leftCell->getGroudColor()
                //leftCell->getGroudColor()
            };

            DrawUtils::drawQuadrilateral(mRenderer, pointsAdjust, colorsAdjust);
        }
    }

    if(upCell != NULL){
        if(mAltitude < upCell->mAltitude){
            SDL_Point pointsAdjust[] = {
                this->getDrawPositioniByCellRelativePosition(Cell::OUTTER_RECT[0], false),
                this->getDrawPositioniByCellRelativePosition(Cell::OUTTER_RECT[1], false),
                upCell->getDrawPositioniByCellRelativePosition(Cell::OUTTER_RECT[2], false),
                upCell->getDrawPositioniByCellRelativePosition(Cell::OUTTER_RECT[3], false)
            };

            SDL_Color colorsAdjust[] = {
                groudColor,
                groudColor,
                upCell->getGroudColor(),
                upCell->getGroudColor()
                //leftCell->getGroudColor()
            };

            DrawUtils::drawQuadrilateral(mRenderer, pointsAdjust, colorsAdjust);
        }
    }
    // //绘制水
    if(mAltitude < 0){
        //SDL_Color colorWater = DrawUtils::overlayColors(getGroudColor(),{0, 0, 255, 128});
        //SDL_Color colorWater = DrawUtils::overlayColors({63, 155, 255, 128},getGroudColor());
        SDL_Color colorWater = {63, 155, 255, 192};
        SDL_Color colorsWater[] = {
            colorWater,
            colorWater,
            colorWater,
            colorWater
        };
        SDL_Point waterPoints[] = {
            this->getDrawPositioniByCellRelativePosition(Cell::OUTTER_RECT[0], true),
            this->getDrawPositioniByCellRelativePosition(Cell::OUTTER_RECT[1], true),
            this->getDrawPositioniByCellRelativePosition(Cell::OUTTER_RECT[2], true),
            this->getDrawPositioniByCellRelativePosition(Cell::OUTTER_RECT[3], true)
        };
        DrawUtils::drawQuadrilateral(mRenderer, waterPoints, colorsWater);
    }
}

SDL_Point Cell::getDrawPosition(SDL_Point cellRelativePosition,bool isWater){
    int landAltitude = mAltitude;
    if(isWater){
        landAltitude = mAltitude > 0 ? mAltitude : 0;
    }
    SDL_Point coverDrawPoint = GridCoordinateConverterUtils::convertToDraw({cellRelativePosition.x, cellRelativePosition.y});
    return {
        static_cast<int>((coverDrawPoint.x)), 
        static_cast<int>((coverDrawPoint.y))
    };
}

SDL_Point Cell::getDrawPositionWithAltitude(SDL_Point cellRelativePosition,bool isWater){
    int landAltitude = mAltitude;
    if(isWater){
        landAltitude = mAltitude > 0 ? mAltitude : 0;
    }
    SDL_Point coverDrawPoint = GridCoordinateConverterUtils::convertToDraw({cellRelativePosition.x, cellRelativePosition.y});
    return {
        static_cast<int>((coverDrawPoint.x)), 
        static_cast<int>((coverDrawPoint.y - landAltitude))
    };
}

SDL_Point Cell::getDrawPositioniByCellRelativePosition(SDL_Point cellRelativePosition,bool isWater){
    int landAltitude = mAltitude;
    if(isWater){
        landAltitude = mAltitude > 0 ? mAltitude : 0;
    }
    int gridPositionX = mLocalX * Game::CELL_SIZE_WIDTH;
    int gridPositionY = mLocalY * Game::CELL_SIZE_HEIGHT;
    SDL_Point coverDrawPoint = GridCoordinateConverterUtils::convertToDraw({gridPositionX + cellRelativePosition.x, gridPositionY + cellRelativePosition.y});
    return {
        static_cast<int>((GameStage::STAGE_POSITION_X + coverDrawPoint.x) * GameStage::GAME_MAP_SCALE), 
        static_cast<int>((GameStage::STAGE_POSITION_Y + coverDrawPoint.y - landAltitude)  * GameStage::GAME_MAP_SCALE)
    };
}

SDL_Point Cell::getDrawPositioniByNearCellPosition(SDL_Point nearPosition,bool isWater){
    int landAltitude = mAltitude;
    if(isWater){
        landAltitude = mAltitude > 0 ? mAltitude : 0;
    }
    int gridPositionX = mLocalX * Game::CELL_SIZE_WIDTH;
    int gridPositionY = mLocalY * Game::CELL_SIZE_HEIGHT;
    SDL_Point coverDrawPoint = GridCoordinateConverterUtils::convertToDraw({gridPositionX + nearPosition.x, gridPositionY + nearPosition.y});
    return {
        static_cast<int>((coverDrawPoint.x) ), 
        static_cast<int>((coverDrawPoint.y - landAltitude))
    };
}

void Cell::drawCellInfo(){
    int gridX = mLocalX * Game::CELL_SIZE_WIDTH;
    int gridY = mLocalY * Game::CELL_SIZE_HEIGHT;

    SDL_Point readPos = GridCoordinateConverterUtils::convertToDraw({gridX, gridY});

    // SDL_Point p1 = (GridCoordinateConverterUtils::convertToDraw({gridX + 0, gridY + 0}));
    // SDL_Point p2 = (GridCoordinateConverterUtils::convertToDraw({gridX + Game::CELL_SIZE_WIDTH, gridY + 0}));
    // SDL_Point p3 = (GridCoordinateConverterUtils::convertToDraw({gridX + Game::CELL_SIZE_WIDTH, gridY + Game::CELL_SIZE_HEIGHT}));
    // SDL_Point p4 = (GridCoordinateConverterUtils::convertToDraw({gridX + 0, gridY + Game::CELL_SIZE_HEIGHT}));
	// SDL_Point points[] = { 
    //     {p1.x + GameStage::STAGE_POSITION_X, p1.y + GameStage::STAGE_POSITION_Y},
    //     {p2.x + GameStage::STAGE_POSITION_X, p2.y + GameStage::STAGE_POSITION_Y},
    //     {p3.x + GameStage::STAGE_POSITION_X, p3.y + GameStage::STAGE_POSITION_Y},
    //     {p4.x + GameStage::STAGE_POSITION_X, p4.y + GameStage::STAGE_POSITION_Y},
    //     {p1.x + GameStage::STAGE_POSITION_X, p1.y + GameStage::STAGE_POSITION_Y}
    // };

    // SDL_Point points[] = { 
    //     {(p1.x + GameStage::STAGE_POSITION_X) * GameStage::GAME_MAP_SCALE, (p1.y + GameStage::STAGE_POSITION_Y) * GameStage::GAME_MAP_SCALE},
    //     {(p2.x + GameStage::STAGE_POSITION_X) * GameStage::GAME_MAP_SCALE, (p2.y + GameStage::STAGE_POSITION_Y) * GameStage::GAME_MAP_SCALE},
    //     {(p3.x + GameStage::STAGE_POSITION_X) * GameStage::GAME_MAP_SCALE, (p3.y + GameStage::STAGE_POSITION_Y) * GameStage::GAME_MAP_SCALE},
    //     {(p4.x + GameStage::STAGE_POSITION_X) * GameStage::GAME_MAP_SCALE, (p4.y + GameStage::STAGE_POSITION_Y) * GameStage::GAME_MAP_SCALE},
    //     {(p1.x + GameStage::STAGE_POSITION_X) * GameStage::GAME_MAP_SCALE, (p1.y + GameStage::STAGE_POSITION_Y) * GameStage::GAME_MAP_SCALE}
    // };

    //if(mLocalX % 50 == 0 && mLocalY % 50 == 0){
        //SDL_SetRenderDrawColor(mRenderer, 0xff, 0x00, 0x00, 0xff);
        // SDL_RenderDrawLines(mRenderer, points, 5);
        //mTextRender->drawText(mText, GameStage::GAME_MAP_SCALE * (GameStage::STAGE_POSITION_X + readPos.x), GameStage::GAME_MAP_SCALE * (GameStage::STAGE_POSITION_Y + readPos.y + Game::CELL_SIZE_HEIGHT / 2), TextRender::RENDER_TYPE_CENTER);
        //mTextRender->drawText(mText, GameStage::GAME_MAP_SCALE * (GameStage::STAGE_POSITION_X + readPos.x), GameStage::GAME_MAP_SCALE * (GameStage::STAGE_POSITION_Y + readPos.y + Game::CELL_SIZE_HEIGHT / 2), TextRender::RENDER_TYPE_CENTER);
    //}
}

int Cell::getGroudAltitude(){
    return mAltitude > 0 ? mAltitude : 0;
}

SDL_Color Cell::getGroudColor(){
    int altitude = mAltitude;
    SDL_Color groudColor;
    //大地的颜色
    groudColor = {185, 122, 87, 255};
    if (altitude > 0) {
        int altitudeLevel = std::round(altitude / 10);
        // 颜色根据 altitude 大小变化，值越大越绿
        // 计算红色分量
        Uint8 r = static_cast<Uint8>((altitudeLevel / 10.0) * 200);
        // 计算绿色分量（固定为 200）
        Uint8 g = 200;
        // 计算蓝色分量
        Uint8 b = static_cast<Uint8>((altitudeLevel / 10.0) * 200);

        groudColor = {r, g, b, 255}; // 设置颜色并设置 alpha 值为 255（完全不透明）
    } else {
        altitude = -altitude;
        int altitudeLevel = std::round(altitude / 10);
        // 计算蓝色分量
        Uint8 r = static_cast<Uint8>(((10 - altitudeLevel) / 10.0) * 180);
        // 计算绿色分量
        Uint8 g = static_cast<Uint8>(150 + ((10 - altitudeLevel) / 10.0) * 100);

        groudColor = {r, g, 255, 255}; // 设置颜色并设置 alpha 值为 255（完全不透明）
    }

    //光照
    if(rightCell != NULL){
        int dark = (rightCell->mAltitude - mAltitude) * 3;
        if(mAltitude < rightCell->mAltitude){
            Uint8 r = groudColor.r - dark > 0 ? groudColor.r - dark : 0;
            Uint8 g = groudColor.g - dark > 0 ? groudColor.g - dark : 0;
            Uint8 b = groudColor.b - dark > 0 ? groudColor.b - dark : 0;
            groudColor = {r, g, b, 255};
        }
        else{
            Uint8 r = groudColor.r - dark < 255 ? groudColor.r - dark : 255;
            Uint8 g = groudColor.g - dark < 255 ? groudColor.g - dark : 255;
            Uint8 b = groudColor.b - dark < 255 ? groudColor.b - dark : 255;
            groudColor = {r, g, b, 255};
        }
    }else if(downCell != NULL){
        int dark = (downCell->mAltitude - mAltitude) * 5;
        if(mAltitude < downCell->mAltitude){
            Uint8 r = groudColor.r - dark > 0 ? groudColor.r - dark : 0;
            Uint8 g = groudColor.g - dark > 0 ? groudColor.g - dark : 0;
            Uint8 b = groudColor.b - dark > 0 ? groudColor.b - dark : 0;
            groudColor = {r, g, b, 255};
        }
        else{
            Uint8 r = groudColor.r - dark < 255 ? groudColor.r - dark : 255;
            Uint8 g = groudColor.g - dark < 255 ? groudColor.g - dark : 255;
            Uint8 b = groudColor.b - dark < 255 ? groudColor.b - dark : 255;
            groudColor = {r, g, b, 255};
        }
    }

    // if(altitude < 0){
    //     groudColor = DrawUtils::overlayColors(groudColor, {0, 0, 255, 128});
    // }
    return groudColor;
}

void Cell::freeTexture(){
    SDL_DestroyTexture(mCellTexture);
}


Cell::~Cell(){
    delete mText;
    //SDL_DestroyRenderer(mRenderer);
}