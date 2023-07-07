#include "Game.h"
#include "GameStage.h"
int GameStage::STAGE_POSITION_X = 0;
int GameStage::STAGE_POSITION_Y = 0;
GameStage::GameStage(SDL_Renderer* renderer){
    mRenderer = renderer;
    mTextRender = new TextRender(renderer);
    mTextRender->loadAssets(15, {0, 255, 0 , 255});
    mCellArray = new Cell*[10];

	mCellArray = new Cell * [Game::MAP_HEIGHT];
	for (int i = 0; i < Game::MAP_HEIGHT; i++) {
		mCellArray[i] = new Cell[Game::MAP_WIDTH];
	}

	// 填充地图数据
	for (int y = 0; y < Game::MAP_HEIGHT; y++) {
		for (int x = 0; x < Game::MAP_WIDTH; x++) {
			// 创建带有初始化参数的 Cell 对象
			Cell cell(mRenderer,mTextRender,x,y,0);
			mCellArray[y][x] = cell;
		}
	}


}

void GameStage::draw(){
	// 打印地图数据
	for (int y = 0; y < Game::MAP_HEIGHT; y++) {
		for (int x = 0; x < Game::MAP_WIDTH; x++) {
			mCellArray[y][x].draw();
		}
	}
}

GameStage::~GameStage(){
    //delete mTextRender;
	for (int i = 0; i < Game::MAP_HEIGHT; i++) {
		delete mCellArray[i];
	}
    delete[] mCellArray;

    delete mTextRender;
}