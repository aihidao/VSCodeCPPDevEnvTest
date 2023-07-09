#include "Game.h"
#include "GameStage.h"
#include <cmath>
#include "GridCoordinateConverterUtils.h"
int GameStage::STAGE_POSITION_X = 0;
int GameStage::STAGE_POSITION_Y = 0;
int GameStage::STAGE_SHOW_LOCAL_X = 0;
int GameStage::STAGE_SHOW_LOCAL_Y = 0;
int GameStage::SELECT_LOCAL_X = 0;
int GameStage::SELECT_LOCAL_Y = 0;

int GameStage::TOP_LEFT_CELL_GRID_X = 0;
int GameStage::TOP_LEFT_CELL_GRID_Y = 0;
int GameStage::BOTTOM_RIGHT_CELL_GRID_X = 0;
int GameStage::BOTTOM_RIGHT_CELL_GRID_Y = 0;
GameStage::GameStage(SDL_Renderer* renderer){
    mRenderer = renderer;
    mTextRender = new TextRender(renderer, 15, {0, 0, 0, 255});
    //mTextRender->loadAssets(15, {0, 255, 0 , 255});

	mCellArray = new Cell* [Game::MAP_HEIGHT * Game::MAP_WIDTH];
	for (int i = 0; i < Game::MAP_HEIGHT  * Game::MAP_WIDTH; i++) {
		mCellArray[i] = new Cell(mRenderer,mTextRender,i % Game::MAP_WIDTH,i / Game::MAP_WIDTH,0);
	}
}

void GameStage::getShowGridInfo(){
	SDL_Point realTopLeft = GridCoordinateConverterUtils::convertToReal({ Game::SCREEN_WIDTH / 2, - 300});
	SDL_Point realBottomRight = GridCoordinateConverterUtils::convertToReal({ Game::SCREEN_WIDTH / 2, Game::SCREEN_HEIGHT  + 300});

	GameStage::TOP_LEFT_CELL_GRID_X = realTopLeft.x / Game::CELL_SIZE_WIDTH;
	GameStage::TOP_LEFT_CELL_GRID_X = GameStage::TOP_LEFT_CELL_GRID_X >= 0 ? GameStage::TOP_LEFT_CELL_GRID_X : 0;
	GameStage::TOP_LEFT_CELL_GRID_X = GameStage::TOP_LEFT_CELL_GRID_X < Game::MAP_WIDTH ? GameStage::TOP_LEFT_CELL_GRID_X : Game::MAP_WIDTH;

	GameStage::TOP_LEFT_CELL_GRID_Y = realTopLeft.y / Game::CELL_SIZE_HEIGHT;
	GameStage::TOP_LEFT_CELL_GRID_Y = GameStage::TOP_LEFT_CELL_GRID_Y >= 0 ? GameStage::TOP_LEFT_CELL_GRID_Y : 0;
	GameStage::TOP_LEFT_CELL_GRID_Y = GameStage::TOP_LEFT_CELL_GRID_Y < Game::MAP_HEIGHT ? GameStage::TOP_LEFT_CELL_GRID_Y : Game::MAP_HEIGHT;

	GameStage::BOTTOM_RIGHT_CELL_GRID_X = realBottomRight.x / Game::CELL_SIZE_WIDTH;
	GameStage::BOTTOM_RIGHT_CELL_GRID_X = GameStage::BOTTOM_RIGHT_CELL_GRID_X >= 0 ? GameStage::BOTTOM_RIGHT_CELL_GRID_X : 0;
	GameStage::BOTTOM_RIGHT_CELL_GRID_X = GameStage::BOTTOM_RIGHT_CELL_GRID_X < Game::MAP_WIDTH ? GameStage::BOTTOM_RIGHT_CELL_GRID_X : Game::MAP_WIDTH;

	GameStage::BOTTOM_RIGHT_CELL_GRID_Y = realBottomRight.y / Game::CELL_SIZE_HEIGHT;
	GameStage::BOTTOM_RIGHT_CELL_GRID_Y = GameStage::BOTTOM_RIGHT_CELL_GRID_Y >= 0 ? GameStage::BOTTOM_RIGHT_CELL_GRID_Y : 0;
	GameStage::BOTTOM_RIGHT_CELL_GRID_Y = GameStage::BOTTOM_RIGHT_CELL_GRID_Y < Game::MAP_HEIGHT ? GameStage::BOTTOM_RIGHT_CELL_GRID_Y : Game::MAP_HEIGHT;
}

void GameStage::handleEvent(SDL_Event* e){
	if (e->type == SDL_MOUSEBUTTONDOWN) {
		if (e->button.button == SDL_BUTTON_RIGHT) {
			mouseDown(e);
		}
	}
		else if (e->type == SDL_MOUSEMOTION) {
			mouseMove(e);
		}
	else if (e->type == SDL_MOUSEBUTTONUP) {
		if (e->button.button == SDL_BUTTON_RIGHT) {
			mouseUp(e);
		}
	}
}

void GameStage::mouseDown(SDL_Event* e) {
	mDownMovePositionX = e->button.x;
	mDownMovePositionY = e->button.y;
	mIsMove = true;
}

void GameStage::mouseMove(SDL_Event* e) {

	if (mIsMove) {
		GameStage::STAGE_POSITION_X += e->motion.xrel;
		GameStage::STAGE_POSITION_Y += e->motion.yrel;

		getShowGridInfo();
	}
}

void GameStage::mouseUp(SDL_Event* e) {
	double moveDis = std::sqrt(std::pow(mDownMovePositionX - e->button.x, 2) + std::pow(mDownMovePositionY - e->button.y, 2));
		if (moveDis < 5.0) {
			printf("You click the map!\n");
		}
		mDownMovePositionX = 0;
		mDownMovePositionY = 0;
		mIsMove = false;
}

void GameStage::draw(){
	// for (int y = 0; y < Game::MAP_HEIGHT; y++) {
	// 	for (int x = 0; x < Game::MAP_WIDTH; x++) {
	// 		mCellArray[y * Game::MAP_WIDTH + x]->draw();
	// 	}
	// }
	// 打印地图数据
	for (int y = GameStage::TOP_LEFT_CELL_GRID_Y; y < GameStage::BOTTOM_RIGHT_CELL_GRID_Y; y++) {
		for (int x = GameStage::TOP_LEFT_CELL_GRID_X; x < GameStage::BOTTOM_RIGHT_CELL_GRID_X; x++) {
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