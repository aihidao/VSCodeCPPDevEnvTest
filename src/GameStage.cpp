#include "Game.h"
#include "GameStage.h"
#include "MapGenerator.h"
#include <cmath>
#include "GridCoordinateConverterUtils.h"
int GameStage::STAGE_POSITION_X = 1000;
int GameStage::STAGE_POSITION_Y = 1000;
double GameStage::GAME_MAP_SCALE = 1;
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

	mDebugInfoBox = new DebugInfoBox(mRenderer);
	mFpsText = new Text("UNDEFINED");
	mMousePosition = new Text("UNDEFINED");
	mMouseSelectPos = new Text("UNDEFINED");
	mStagePosition = new Text("UNDEFINED");
	mStageShow = new Text("UNDEFINED");
	mDebugInfoBox->push(mFpsText);
	mDebugInfoBox->push(mMousePosition);
	mDebugInfoBox->push(mMouseSelectPos);
	mDebugInfoBox->push(mStagePosition);
	mDebugInfoBox->push(mStageShow);
}

void GameStage::initGrid(){
	mCellArray = new Cell* [Game::MAP_HEIGHT * Game::MAP_WIDTH];
	MapGenerator mapGenerator = MapGenerator(Game::MAP_WIDTH, Game::MAP_HEIGHT, 0);
	//init Cells
	for (int i = 0; i < Game::MAP_HEIGHT  * Game::MAP_WIDTH; i++) {
		++Game::initProgress;
		int gridX = i % Game::MAP_WIDTH;
		int gridY = i / Game::MAP_WIDTH;
		int altitude = mapGenerator.mAltitudeMap[i];
		mCellArray[i] = new Cell(mRenderer,mTextRender, gridX, gridY,0);

		// Linked Cell
		if(gridX > 0){
			mCellArray[i]->leftCell = mCellArray[i - 1];
			mCellArray[i - 1]->rightCell = mCellArray[i];
		}

		if(gridY > 0){
			mCellArray[i]->upCell = mCellArray[i - Game::MAP_WIDTH];
			mCellArray[i - Game::MAP_WIDTH]->downCell = mCellArray[i];
		}

		// Setting value
		mCellArray[i]->setAltitude(altitude);
	}

	//init CellChunks
	int chunkIndexGridX = 0;
	int chunkIndexGridY = 0;
	mCellChunkArrayWidth = std::ceil(static_cast<double>(Game::MAP_WIDTH) / Game::CHUNK_SIZE_WIDTH);
	mCellChunkArrayHeight = std::ceil(static_cast<double>(Game::MAP_WIDTH) / Game::CHUNK_SIZE_HEIGHT);
	mCellChunkArray = new CellChunk* [mCellChunkArrayWidth * mCellChunkArrayHeight];
	for(int j = 0; j < mCellChunkArrayHeight; j++){
		for(int i = 0; i < mCellChunkArrayWidth; i++){
			int chunkSizeWidth = i * Game::CHUNK_SIZE_WIDTH + Game::CHUNK_SIZE_WIDTH > Game::MAP_WIDTH ? Game::MAP_WIDTH - i * Game::CHUNK_SIZE_WIDTH : Game::CHUNK_SIZE_WIDTH;
			int chunkSizeHeight = j * Game::CHUNK_SIZE_HEIGHT + Game::CHUNK_SIZE_HEIGHT > Game::MAP_HEIGHT ? Game::MAP_HEIGHT - j * Game::CHUNK_SIZE_HEIGHT : Game::CHUNK_SIZE_HEIGHT;
			int index = j * mCellChunkArrayWidth + i;
			mCellChunkArray[index] = new CellChunk(mRenderer, i, j, chunkSizeWidth, chunkSizeHeight, mCellArray);
		
			//Linked Cell
			if(i > 0){
				mCellChunkArray[index]->leftCellChunk = mCellChunkArray[index - 1];
				mCellChunkArray[index - 1]->rightCellChunk = mCellChunkArray[index];
			}

			if(j > 0){
				mCellChunkArray[index]->upCellChunk = mCellChunkArray[index - mCellChunkArrayWidth];
				mCellChunkArray[index - mCellChunkArrayWidth]->downCellChunk = mCellChunkArray[index];
			}
		}
	}
}

void GameStage::getShowGridInfo(){
	SDL_Point realTopLeft = GridCoordinateConverterUtils::convertToReal({static_cast<int>( (Game::SCREEN_WIDTH / 2) / GameStage::GAME_MAP_SCALE),static_cast<int>((- 300) / GameStage::GAME_MAP_SCALE)});
	SDL_Point realBottomRight = GridCoordinateConverterUtils::convertToReal({ static_cast<int>((Game::SCREEN_WIDTH / 2) / GameStage::GAME_MAP_SCALE), static_cast<int>((Game::SCREEN_HEIGHT  + 300) / GameStage::GAME_MAP_SCALE)});

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

bool GameStage::handleEvent(SDL_Event* e){
	bool quit = false;
	while(SDL_PollEvent(e) != 0){
		if (e->type == SDL_QUIT) {
			quit = true;
		}else if (e->type == SDL_MOUSEBUTTONDOWN) {
			if (e->button.button == SDL_BUTTON_RIGHT) {
				mouseDown(e);
			}
		}else if (e->type == SDL_MOUSEMOTION) {
			SDL_GetMouseState(&mMouseX, &mMouseY);
			std::string mousePosInfo = "Mouse Pos :(" + std::to_string(mMouseX) + "," + std::to_string(mMouseY) + ")";
			mMousePosition->setStr(mousePosInfo);
			std::string stagePosInfo = "Stage Pos :(" + std::to_string(GameStage::STAGE_POSITION_X) + "," + std::to_string(GameStage::STAGE_POSITION_Y) + ")";
			mStagePosition->setStr(stagePosInfo);
			std::string stageShowInfo = "Stage Show:(" + std::to_string(GameStage::TOP_LEFT_CELL_GRID_X) + "," + std::to_string(GameStage::TOP_LEFT_CELL_GRID_Y) + ") <-> (" + std::to_string(GameStage::BOTTOM_RIGHT_CELL_GRID_X) + "," + std::to_string(GameStage::BOTTOM_RIGHT_CELL_GRID_Y) + ")" ;
			mStageShow->setStr(stageShowInfo);

			SDL_Point realPos = GridCoordinateConverterUtils::convertToReal({mMouseX, mMouseY});
			int posX = realPos.x / Game::CELL_SIZE_WIDTH;
			int posY = realPos.y / Game::CELL_SIZE_HEIGHT;

			std::string mouseSelectInfo = "Mouse Select Pos :(" + std::to_string(posX) + "," + std::to_string(posY) + ")";
			mMouseSelectPos->setStr(mouseSelectInfo);

			mouseMove(e);
			}
		else if (e->type == SDL_MOUSEBUTTONUP) {
			if (e->button.button == SDL_BUTTON_RIGHT) {
				mouseUp(e);
			}
		} else if (e->type == SDL_MOUSEWHEEL) {
			int x = e->wheel.x; // 水平方向的滚动量
        	int y = e->wheel.y; // 垂直方向的滚动量
			int mouseX, mouseY;
        	Uint32 buttonState = SDL_GetMouseState(&mouseX, &mouseY);
			// 根据滚动量执行相应操作
			double oldScale = GameStage::GAME_MAP_SCALE;
			if (y > 0) {
				// 向上滚动
				// 处理滚轮向上滚动的事件
				if(GameStage::GAME_MAP_SCALE + 0.1 <= 1.0){
					GameStage::GAME_MAP_SCALE += 0.1;
				}else{
					GameStage::GAME_MAP_SCALE = 1.0;
				}
			} else if (y < 0) {
				// 向下滚动
				// 处理滚轮向下滚动的事件
				if(GameStage::GAME_MAP_SCALE - 0.1 >= 0.1){
					GameStage::GAME_MAP_SCALE -= 0.1;
				}else{
					GameStage::GAME_MAP_SCALE = 0.1;
				}
			}

			if(std::abs(oldScale - GameStage::GAME_MAP_SCALE) > 1e-9){
				//int transX = (mouseX - mouseY);
    			//int transY = (mouseX + mouseY) / 2;
				//std::cout << std::round(((GameStage::GAME_MAP_SCALE / oldScale) * (mouseX - GameStage::STAGE_POSITION_X)) - mouseX + GameStage::STAGE_POSITION_X) ;
				GameStage::STAGE_POSITION_X -= std::round(((GameStage::GAME_MAP_SCALE/oldScale - 1) * (mouseX))) / GameStage::GAME_MAP_SCALE;
				GameStage::STAGE_POSITION_Y -= std::round(((GameStage::GAME_MAP_SCALE/oldScale - 1) * (mouseY))) / GameStage::GAME_MAP_SCALE;
			}

			getShowGridInfo();
		}else{
			
		}
		mDebugInfoBox->handleEvent(e);
	}
	return quit;
}

void GameStage::calculateFps() {
	frameCount++;
	Uint32 frameTime = SDL_GetTicks() - frameStart;
	if (frameTime > 25) {
		float frameRate = 0.0f;
		frameRate = frameCount / ((frameTime) / 1000.0f);
		frameCount = 0;
		//std::cout << "Current FPS: " << frameRate << std::endl;
		frameStart = SDL_GetTicks();
		std::string fpsInfo = "FPS:" + std::to_string(frameRate);
		mFpsText->setStr(fpsInfo);
	}
}

void GameStage::mouseDown(SDL_Event* e) {
	mDownMovePositionX = e->button.x;
	mDownMovePositionY = e->button.y;
	mIsMove = true;
}

void GameStage::mouseMove(SDL_Event* e) {

	if (mIsMove) {
		GameStage::STAGE_POSITION_X += e->motion.xrel / GameStage::GAME_MAP_SCALE;
		GameStage::STAGE_POSITION_Y += e->motion.yrel / GameStage::GAME_MAP_SCALE;

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
	calculateFps();
	//SDL_SetRenderDrawColor(mRenderer, 0, 0, 0, 0xFF);
	SDL_SetRenderDrawColor(mRenderer, 128, 128, 128, 0xFF);
	//Clear screen
	SDL_RenderClear(mRenderer);

	// for (int y = 0; y < Game::MAP_HEIGHT; y++) {
	// 	for (int x = 0; x < Game::MAP_WIDTH; x++) {
	// 		mCellArray[y * Game::MAP_WIDTH + x]->draw();
	// 	}
	// }

	// for (int y = GameStage::TOP_LEFT_CELL_GRID_Y; y < GameStage::BOTTOM_RIGHT_CELL_GRID_Y; y++) {
	// 	for (int x = GameStage::TOP_LEFT_CELL_GRID_X; x < GameStage::BOTTOM_RIGHT_CELL_GRID_X; x++) {
	// 		mCellArray[y * Game::MAP_WIDTH + x]->drawCellInfo();
	// 	}
	// }
	//mCellChunkArray[0]->draw();
	int createCount = 0;
	for(int i = 0; i < mCellChunkArrayWidth * mCellChunkArrayHeight; i++){
		if(!mCellChunkArray[i]->draw()){
			createCount++;
		}

		if(createCount > 5){
			break;
		}
	}
	mDebugInfoBox->draw();

	SDL_RenderPresent(mRenderer);
}

GameStage::~GameStage(){
    //delete mTextRender;
	for (int i = 0; i < Game::MAP_HEIGHT * Game::MAP_WIDTH; i++) {
		delete mCellArray[i];
	}
	delete mFpsText;
	delete mMousePosition;
	delete mMouseSelectPos;
	delete mStagePosition;
	delete mStageShow;
	delete mDebugInfoBox;
    delete[] mCellArray;
    delete mTextRender;
}