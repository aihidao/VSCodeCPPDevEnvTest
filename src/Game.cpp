/*This source code copyrighted by Lazy Foo' Productions 2004-2023
and may not be redistributed without written permission.*/

//Using SDL, SDL_image, standard IO, and strings
#include "Game.h"
#include <SDL_ttf.h>
#include <iostream>
#include <stdio.h>
#include <string>
#include <cmath>
#include <Game.h>
#include "GridCoordinateConverterUtils.h"
int	Game::SCREEN_WIDTH = 800;
int	Game::SCREEN_HEIGHT = 600;

int	Game::MAP_WIDTH = 1000;
int	Game::MAP_HEIGHT = 1000;

int	Game::CELL_SIZE_WIDTH = 50;
int	Game::CELL_SIZE_HEIGHT = 50;
Game::Game(){
	printf("Screen width: %d\n", Game::SCREEN_WIDTH);
	printf("Screen height: %d\n", Game::SCREEN_HEIGHT);

	printf("Map width: %d\n", Game::MAP_WIDTH);
	printf("Map height: %d\n", Game::MAP_HEIGHT);
}

void Game::update() {
	//Main loop flag
	bool quit = false;

	//Event handler
	SDL_Event e;

	//While application is running
	while (!quit)
	{
		//Handle events on queue
		quit = handleEvent(&e);
		calculateFps();
		updateDraw();
	}
}

bool Game::handleEvent(SDL_Event* e)
{
	bool quit = false;
	while (SDL_PollEvent(e) != 0)
	{
		//User requests quit
		if (e->type == SDL_QUIT) {
			quit = true;
		}else if (e->type == SDL_USEREVENT) {
			//updateDraw();
		}
		else if (e->type == SDL_MOUSEMOTION) {
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
		}
		else if (e->type == SDL_MOUSEBUTTONDOWN) {
			
		}
		else if (e->type == SDL_MOUSEBUTTONUP) {

		}
		mGameStage->handleEvent(e);
		mDebugInfoBox->handleEvent(e);
	}
	return quit;
}

void Game::updateDraw() {
	SDL_SetRenderDrawColor(mRenderer, 153, 217, 234, 0xFF);
	//Clear screen
	SDL_RenderClear(mRenderer);

	mGameStage->draw();

	mDebugInfoBox->draw();

	//Update screen
	SDL_RenderPresent(mRenderer);
}

bool Game::loadWidget()
{
	//Loading success flag
	bool success = true;
	

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
	//mTextRender = new TextRender(mRenderer);
	mGameStage = new GameStage(mRenderer);
	mGameStage->getShowGridInfo();
	return success;
}

void Game::calculateFps() {
	
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

bool Game::start() {
	//Start up SDL and create window
	if (!init())
	{
		printf("Failed to initialize!\n");
	}
	else
	{
		//Load media
		if (!loadWidget())
		{
			printf("Failed to load media!\n");
		}
		else
		{
			//timmers
			update();
		}
	}

	//Free resources and close SDL
	close();
	return true;
}


bool Game::init()
{
	//Initialization flag
	bool success = true;

	//Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
		success = false;
	}
	else
	{
		//Set texture filtering to linear
		if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
		{
			printf("Warning: Linear texture filtering not enabled!");
		}

		//Create window
		this->mWindow = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (mWindow == NULL)
		{
			printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
			success = false;
		}
		else
		{
			//Create renderer for window
			mRenderer = SDL_CreateRenderer(mWindow, -1, SDL_RENDERER_ACCELERATED);
			if (mRenderer == NULL)
			{
				printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
				success = false;
			}
			else
			{

				//Initialize renderer color
				SDL_SetRenderDrawColor(mRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

				//Initialize PNG loading
				int imgFlags = IMG_INIT_PNG;
				if (!(IMG_Init(imgFlags) & imgFlags))
				{
					printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
					success = false;
				}

				//Initialize SDL_ttf
				if (TTF_Init() == -1)
				{
					printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
					success = false;
				}
			}
		}
	}
	return success;
}

void Game::close()
{
	//delete mTextRender;
	delete mFpsText;
	delete mMousePosition;
	delete mMouseSelectPos;
	delete mStagePosition;
	delete mStageShow;
	delete mDebugInfoBox;
	delete mGameStage;
	//Destroy window	
	SDL_DestroyRenderer(mRenderer);
	SDL_DestroyWindow(mWindow);
	mWindow = NULL;
	mRenderer = NULL;

	//Quit SDL subsystems
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
}

