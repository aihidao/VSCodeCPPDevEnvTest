#include "Cell.h"
#include "Game.h"
#include "GameStage.h"
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
    int positionX = GameStage::STAGE_POSITION_X + (mLocalX - mLocalY) * Game::CELL_SIZE_WIDTH;
	int positionY = GameStage::STAGE_POSITION_Y + (mLocalY + mLocalX) * Game::CELL_SIZE_HEIGHT;

    // 菱形的四个顶点坐标
	int x1 = positionX - Game::CELL_SIZE_WIDTH, y1 = positionY + 0; // 顶部顶点
	int x2 = positionX + 0, y2 = positionY + Game::CELL_SIZE_HEIGHT; // 右侧顶点
	int x3 = positionX + Game::CELL_SIZE_WIDTH, y3 = positionY + 0; // 底部顶点
	int x4 = positionX + 0, y4 = positionY - Game::CELL_SIZE_HEIGHT; // 左侧顶点
	SDL_Point points[] = { {x1, y1}, {x2, y2}, {x3, y3}, {x4, y4}, {x1, y1} };
    SDL_SetRenderDrawColor(mRenderer, 0xff, 0x00, 0x00, 0xff);
	SDL_RenderDrawLines(mRenderer, points, 5);

    mTextRender->drawText(mText,positionX,positionY,TextRender::RENDER_TYPE_CENTER);
}

Cell::~Cell(){
    delete mText;
    //SDL_DestroyRenderer(mRenderer);
}