#include "Cell.h"
#include "Game.h"
#include <cmath>
#include "MapGenerator.h"
#include "GameStage.h"
#include "GridCoordinateConverterUtils.h"

// ---->
// |   |
// <----
SDL_Point Cell::OUTTER_RECT[4] = { 
    {0, 0}, 
    {Game::CELL_SIZE_WIDTH , 0}, 
    {Game::CELL_SIZE_WIDTH, Game::CELL_SIZE_HEIGHT}, 
    {0, Game::CELL_SIZE_HEIGHT} 
};

SDL_Point Cell::INNER_RECT[4] = { 
    {Game::CELL_SIZE_WIDTH / 4, Game::CELL_SIZE_HEIGHT / 4}, 
    {3 * Game::CELL_SIZE_WIDTH / 4 , Game::CELL_SIZE_HEIGHT / 4}, 
    {3 * Game::CELL_SIZE_WIDTH / 4, 3 * Game::CELL_SIZE_HEIGHT / 4}, 
    {Game::CELL_SIZE_WIDTH / 4, 3 * Game::CELL_SIZE_HEIGHT / 4} 
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

void Cell::draw(){
    SDL_Color groudColor = getGroudColor(mAltitude);

    SDL_Point points[] = { 
            getDrawPositioniByCellRelativePosition(Cell::INNER_RECT[0]),
            getDrawPositioniByCellRelativePosition(Cell::INNER_RECT[1]),
            getDrawPositioniByCellRelativePosition(Cell::INNER_RECT[2]),
            getDrawPositioniByCellRelativePosition(Cell::INNER_RECT[3]),
            getDrawPositioniByCellRelativePosition(Cell::INNER_RECT[0])
        };
    // 设置颜色
    SDL_SetRenderDrawColor(mRenderer, 255, 0, 0, 255);


    const std::vector< SDL_Vertex > gourdRightVert =
    {
        { SDL_FPoint{ (float)points[1].x, (float)points[1].y}, groudColor, SDL_FPoint{ 0 }, },
        { SDL_FPoint{ (float)points[2].x, (float)points[2].y}, groudColor, SDL_FPoint{ 0 }, },
        { SDL_FPoint{ (float)points[3].x, (float)points[3].y}, groudColor, SDL_FPoint{ 0 }, },
    };
    SDL_RenderGeometry( mRenderer, nullptr, gourdRightVert.data(), gourdRightVert.size(), nullptr, 0 );
    const std::vector< SDL_Vertex > gourdLeftVert =
    {
        { SDL_FPoint{ (float)points[1].x, (float)points[1].y}, groudColor, SDL_FPoint{ 0 }, },
        { SDL_FPoint{ (float)points[4].x, (float)points[4].y}, groudColor, SDL_FPoint{ 0 }, },
        { SDL_FPoint{ (float)points[3].x, (float)points[3].y}, groudColor, SDL_FPoint{ 0 }, },
    };
    SDL_RenderGeometry( mRenderer, nullptr, gourdLeftVert.data(), gourdLeftVert.size(), nullptr, 0 );

    //
    if(leftCell != NULL){
        //SDL_Color testColor = {255,0,0,255};
        SDL_Point pointsLeft[] = { 
            this->getDrawPositioniByCellRelativePosition(Cell::INNER_RECT[0]),
            this->getDrawPositioniByCellRelativePosition(Cell::INNER_RECT[3]),
            leftCell->getDrawPositioniByCellRelativePosition(Cell::INNER_RECT[2])
        };
        const std::vector< SDL_Vertex > leftOutterGroud =
        {
            { SDL_FPoint{ (float)pointsLeft[0].x, (float)pointsLeft[0].y}, groudColor, SDL_FPoint{ 0 }, },
            { SDL_FPoint{ (float)pointsLeft[1].x, (float)pointsLeft[1].y}, groudColor, SDL_FPoint{ 0 }, },
            { SDL_FPoint{ (float)pointsLeft[2].x, (float)pointsLeft[2].y}, groudColor, SDL_FPoint{ 0 }, },
        };
        SDL_RenderGeometry( mRenderer, nullptr, leftOutterGroud.data(), leftOutterGroud.size(), nullptr, 0 );
    }

    if(upCell != NULL){
        //SDL_Color testColor = {255,0,0,255};
        SDL_Point pointsUp[] = { 
            this->getDrawPositioniByCellRelativePosition(Cell::INNER_RECT[0]),
            this->getDrawPositioniByCellRelativePosition(Cell::INNER_RECT[1]),
            upCell->getDrawPositioniByCellRelativePosition(Cell::INNER_RECT[3])
        };
        const std::vector< SDL_Vertex > upOutterGroud =
        {
            { SDL_FPoint{ (float)pointsUp[0].x, (float)pointsUp[0].y}, groudColor, SDL_FPoint{ 0 }, },
            { SDL_FPoint{ (float)pointsUp[1].x, (float)pointsUp[1].y}, groudColor, SDL_FPoint{ 0 }, },
            { SDL_FPoint{ (float)pointsUp[2].x, (float)pointsUp[2].y}, groudColor, SDL_FPoint{ 0 }, },
        };
        SDL_RenderGeometry( mRenderer, nullptr, upOutterGroud.data(), upOutterGroud.size(), nullptr, 0 );
    }

    if(rightCell != NULL){
        //SDL_Color testColor = {255,0,0,255};
        SDL_Point pointsRight[] = { 
            this->getDrawPositioniByCellRelativePosition(Cell::INNER_RECT[1]),
            this->getDrawPositioniByCellRelativePosition(Cell::INNER_RECT[2]),
            rightCell->getDrawPositioniByCellRelativePosition(Cell::INNER_RECT[0])
        };
        const std::vector< SDL_Vertex > rightOutterGroud =
        {
            { SDL_FPoint{ (float)pointsRight[0].x, (float)pointsRight[0].y}, groudColor, SDL_FPoint{ 0 }, },
            { SDL_FPoint{ (float)pointsRight[1].x, (float)pointsRight[1].y}, groudColor, SDL_FPoint{ 0 }, },
            { SDL_FPoint{ (float)pointsRight[2].x, (float)pointsRight[2].y}, groudColor, SDL_FPoint{ 0 }, },
        };
        SDL_RenderGeometry( mRenderer, nullptr, rightOutterGroud.data(), rightOutterGroud.size(), nullptr, 0 );
    }

    if(downCell != NULL){
        //SDL_Color testColor = {255,0,0,255};
        SDL_Point pointsDown[] = { 
            this->getDrawPositioniByCellRelativePosition(Cell::INNER_RECT[2]),
            this->getDrawPositioniByCellRelativePosition(Cell::INNER_RECT[3]),
            downCell->getDrawPositioniByCellRelativePosition(Cell::INNER_RECT[1])
        };
        const std::vector< SDL_Vertex > downOutterGroud =
        {
            { SDL_FPoint{ (float)pointsDown[0].x, (float)pointsDown[0].y}, groudColor, SDL_FPoint{ 0 }, },
            { SDL_FPoint{ (float)pointsDown[1].x, (float)pointsDown[1].y}, groudColor, SDL_FPoint{ 0 }, },
            { SDL_FPoint{ (float)pointsDown[2].x, (float)pointsDown[2].y}, groudColor, SDL_FPoint{ 0 }, },
        };
        SDL_RenderGeometry( mRenderer, nullptr, downOutterGroud.data(), downOutterGroud.size(), nullptr, 0 );
    }

    // if(mAltitude > 0){
    //     SDL_Point linePoints[] = { 
    //         getDrawPositioniByCellRelativePosition(Cell::OUTTER_RECT[0]),
    //         getDrawPositioniByCellRelativePosition(Cell::OUTTER_RECT[1]),
    //         getDrawPositioniByCellRelativePosition(Cell::OUTTER_RECT[2]),
    //         getDrawPositioniByCellRelativePosition(Cell::OUTTER_RECT[3]),
    //     };

    //     SDL_SetRenderDrawColor(mRenderer, 142, 64, 54, 128);
    //     //SDL_RenderDrawLines(mRenderer, linePoints, 3);
    //     //SDL_RenderDrawLine(mRenderer,);
    //     if(upCell == NULL || mAltitude > upCell->mAltitude){
    //         SDL_RenderDrawLine(mRenderer, linePoints[0].x, linePoints[0].y, linePoints[1].x, linePoints[1].y);
    //     }

    //     if(leftCell == NULL || mAltitude > leftCell->mAltitude){
    //         SDL_RenderDrawLine(mRenderer, linePoints[0].x, linePoints[0].y, linePoints[3].x, linePoints[3].y);
    //     }

    // }

}

SDL_Point Cell::getDrawPositioniByCellRelativePosition(SDL_Point cellRelativePosition){
    int landAltitude = mAltitude > 0 ? mAltitude : 0;
    int gridPositionX = mLocalX * Game::CELL_SIZE_WIDTH;
    int gridPositionY = mLocalY * Game::CELL_SIZE_HEIGHT;
    SDL_Point coverDrawPoint = GridCoordinateConverterUtils::convertToDraw({gridPositionX + cellRelativePosition.x, gridPositionY + cellRelativePosition.y});
    return {
        static_cast<int>((GameStage::STAGE_POSITION_X + coverDrawPoint.x) * GameStage::GAME_MAP_SCALE), 
        static_cast<int>((GameStage::STAGE_POSITION_Y + coverDrawPoint.y - landAltitude)  * GameStage::GAME_MAP_SCALE)
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



SDL_Color Cell::getGroudColor(int altitude){
    SDL_Color color;
    if(altitude < -100){
        altitude = -100;
    }

    if(altitude > 100){
        altitude = 100;
    }
    
    if (altitude > 0) {
        int altitudeLevel = std::round(altitude / 10);
        // 颜色根据 altitude 大小变化，值越大越绿
        // 计算红色分量
        Uint8 r = static_cast<Uint8>((altitudeLevel / 10.0) * 200);
        // 计算绿色分量（固定为 200）
        Uint8 g = 200;
        // 计算蓝色分量
        Uint8 b = static_cast<Uint8>((altitudeLevel / 10.0) * 200);

        color = {r, g, b, 255}; // 设置颜色并设置 alpha 值为 255（完全不透明）
    } else {
        altitude = -altitude;
        int altitudeLevel = std::round(altitude / 10);
        // 计算蓝色分量
        Uint8 r = static_cast<Uint8>(((10 - altitudeLevel) / 10.0) * 180);
        // 计算绿色分量
        Uint8 g = static_cast<Uint8>(150 + ((10 - altitudeLevel) / 10.0) * 100);

        color = {r, g, 255, 255}; // 设置颜色并设置 alpha 值为 255（完全不透明）
    }

    return color;
}


Cell::~Cell(){
    delete mText;
    //SDL_DestroyRenderer(mRenderer);
}