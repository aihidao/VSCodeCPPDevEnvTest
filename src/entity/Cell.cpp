#include "Cell.h"
#include "Game.h"
#include <cmath>
#include "GameStage.h"
#include "GridCoordinateConverterUtils.h"
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
    std::string positionInfo = "(" + std::to_string(mLocalX) + "," + std::to_string(mLocalY) + ")";
    //printf("init info:%s\n",positionInfo.c_str());
    mText = new Text(positionInfo.c_str());
    //mText->setStr(positionInfo);
}

void Cell::draw(){
    int gridX = mLocalX * Game::CELL_SIZE_WIDTH;
    int gridY = mLocalY * Game::CELL_SIZE_HEIGHT;

    SDL_Point readPos = GridCoordinateConverterUtils::convertToDraw({gridX, gridY});

    SDL_Point p1 = (GridCoordinateConverterUtils::convertToDraw({gridX + 0, gridY + 0}));
    SDL_Point p2 = (GridCoordinateConverterUtils::convertToDraw({gridX + Game::CELL_SIZE_WIDTH, gridY + 0}));
    SDL_Point p3 = (GridCoordinateConverterUtils::convertToDraw({gridX + Game::CELL_SIZE_WIDTH, gridY + Game::CELL_SIZE_HEIGHT}));
    SDL_Point p4 = (GridCoordinateConverterUtils::convertToDraw({gridX + 0, gridY + Game::CELL_SIZE_HEIGHT}));
	SDL_Point points[] = { 
        {p1.x + GameStage::STAGE_POSITION_X, p1.y + GameStage::STAGE_POSITION_Y},
        {p2.x + GameStage::STAGE_POSITION_X, p2.y + GameStage::STAGE_POSITION_Y},
        {p3.x + GameStage::STAGE_POSITION_X, p3.y + GameStage::STAGE_POSITION_Y},
        {p4.x + GameStage::STAGE_POSITION_X, p4.y + GameStage::STAGE_POSITION_Y},
        {p1.x + GameStage::STAGE_POSITION_X, p1.y + GameStage::STAGE_POSITION_Y}
    };
    // 设置颜色
    SDL_SetRenderDrawColor(mRenderer, 255, 0, 0, 255);

    SDL_Color groudColor = {255, 255, 0, 255};
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

    SDL_SetRenderDrawColor(mRenderer, 0xff, 0x00, 0x00, 0xff);
    SDL_RenderDrawLines(mRenderer, points, 5);
    mTextRender->drawText(mText, GameStage::STAGE_POSITION_X + readPos.x, GameStage::STAGE_POSITION_Y + readPos.y + Game::CELL_SIZE_HEIGHT / 2, TextRender::RENDER_TYPE_CENTER);
    }


Cell::~Cell(){
    delete mText;
    //SDL_DestroyRenderer(mRenderer);
}