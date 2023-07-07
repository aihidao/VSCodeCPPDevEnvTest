#include "Game.h"
#include "GameStage.h"
int GameStage::STAGE_POSITION_X = 0;
int GameStage::STAGE_POSITION_Y = 0;
GameStage::GameStage(SDL_Renderer* renderer){
    mRenderer = renderer;
    mTextRender = new TextRender(renderer);
    mTextRender->loadAssets(15, {0, 255, 0 , 255});

	mCellArray = new Cell* [Game::MAP_HEIGHT * Game::MAP_WIDTH];
	for (int i = 0; i < Game::MAP_HEIGHT  * Game::MAP_WIDTH; i++) {
		mCellArray[i] = new Cell(mRenderer,mTextRender,i % Game::MAP_WIDTH,i / Game::MAP_WIDTH,0);
	}
}

void GameStage::draw(){
	// 打印地图数据
	for (int y = 0; y < Game::MAP_HEIGHT; y++) {
		for (int x = 0; x < Game::MAP_WIDTH; x++) {
			mCellArray[y * Game::MAP_WIDTH + x]->draw();
		}
	}
}

GameStage::~GameStage(){
    //delete mTextRender;
	for (int i = 0; i < Game::MAP_HEIGHT * Game::MAP_WIDTH; i++) {
		delete mCellArray[i];
	}
    delete[] mCellArray;
    delete mTextRender;
}