#include "GameStage.h"
#include "GameConfig.h"
GameStage::GameStage(SDL_Renderer* renderer){
    mRenderer = renderer;
    mTextRender = new TextRender(renderer);
    mTextRender->loadAssets(15);
    mCellArray = new Cell*[10];

	mCellArray = new Cell * [MAP_HEIGHT];
	for (int i = 0; i < MAP_HEIGHT; i++) {
		mCellArray[i] = new Cell[MAP_WIDTH];
	}

	// 填充地图数据
	for (int y = 0; y < MAP_HEIGHT; y++) {
		for (int x = 0; x < MAP_WIDTH; x++) {
			// 创建带有初始化参数的 Cell 对象
			Cell cell(mRenderer,mTextRender,x,y,0);
			mCellArray[y][x] = cell;
		}
	}
}

void GameStage::draw(){
	// 打印地图数据
	for (int y = 0; y < MAP_HEIGHT; y++) {
		for (int x = 0; x < MAP_WIDTH; x++) {
			mCellArray[y][x].draw();
		}
	}
}

GameStage::~GameStage(){
    //delete mTextRender;
    for(int i = 0;i < 10;i++){
        delete mCellArray[i];
    }
    delete[] mCellArray;

    delete mTextRender;
}