/*This source code copyrighted by Lazy Foo' Productions 2004-2023
and may not be redistributed without written permission.*/

//Using SDL, SDL_image, standard IO, and strings
#include "Game.h"
#include "SDL_ttf.h"
#include <SDL_thread.h>
#include <iostream>
#include <stdio.h>
#include <string>
#include <cmath> 
#include <Game.h>
#include <thread>
#include "GridCoordinateConverterUtils.h"
int	Game::SCREEN_WIDTH = 1024;
int	Game::SCREEN_HEIGHT = 768;

int	Game::MAP_WIDTH = 1000; 
int	Game::MAP_HEIGHT = 1000;

int	Game::CELL_SIZE_WIDTH = 50;
int	Game::CELL_SIZE_HEIGHT = 50;

int	Game::CHUNK_SIZE_WIDTH = 50;
int	Game::CHUNK_SIZE_HEIGHT = 50;

volatile int Game::initProgress = 0;
Game::Game(){
	printf("Screen width: %d\n", Game::SCREEN_WIDTH);
	printf("Screen height: %d\n", Game::SCREEN_HEIGHT);

	printf("Map width: %d\n", Game::MAP_WIDTH);
	printf("Map height: %d\n", Game::MAP_HEIGHT);
}

static int loading(void* data) {
	try{
		((Game*)data)->calculateGameDate();
	}catch(std::exception& e){
		//其他的错误
		std::cout << "ERROR:" << e.what() << std::endl;
	}
	return 0;
}

static int draw(void* data){
	Game* game = (Game*)data;
	try{
		while(!game->mQuit){
			if(game->mNeedLoading){
				game->mLoadingPage->draw();
			}else{
				game->mGameStage->draw();
			}
		}
	}catch(std::exception& e){
		//其他的错误
		std::cout << "ERROR:" << e.what() << std::endl;
	}
	return 0;
}

bool Game::start() {
	//Start up SDL and create window
	if (!init())
	{
		printf("Failed to initialize!\n");
	}
	else
	{
		initGameEnv();
		mDrawThread = SDL_CreateThread(draw, "drawThread", this);
		SDL_DetachThread(mDrawThread);

		mLoadingThread = SDL_CreateThread(loading, "loadingThread", this);
		SDL_DetachThread(mLoadingThread);
		update();
	}

	//Free resources and close SDL
	close();
	return true;
}

bool Game::initGameEnv(){
	//Load media
	mLoadingPage = new LoadingPage(mRenderer);
	//mTextRender = new TextRender(mRenderer, 15, {0, 255, 0, 255});
	mGameStage = new GameStage(mRenderer);
	return true;
}

bool Game::calculateGameDate()
{
	bool success = true;
	mGameStage->initGrid();
	mGameStage->getShowGridInfo();
	mNeedLoading = false;
	//SDL_Threa(mLoadingThread);	
	return success;
}

// bool Game::handleEvent(SDL_Event* e)
// {
// 	bool quit = false;
// 	while (SDL_PollEvent(e) != 0)
// 	{
// 		//User requests quit
// 		if (e->type == SDL_QUIT) {
// 			quit = true;
// 		}
// 		mGameStage->handleEvent(e);
// 	}
// 	return quit;
// }

void Game::update() {
	//Main loop flag
	bool quit = false;
	//Event handler
	SDL_Event e;

	//While application is running
	while (!quit)
	{
		try
		{
			if(!mNeedLoading){
				//Handle events on queue
				mQuit = mGameStage->handleEvent(&e);
				//mGameStage->draw();
			}else{
				mQuit = mLoadingPage->handleEvent(&e);
				//mLoadingPage->draw();
			}
		}
		catch(std::exception& e)
		{
			//其他的错误
			std::cout << "ERROR:" << e.what() << std::endl;
		}
	}
}

// void Game::updateDraw() {
// 	SDL_SetRenderDrawColor(mRenderer, 153, 217, 234, 0xFF);
// 	//Clear screen
// 	SDL_RenderClear(mRenderer);

// 	mGameStage->draw();

// 	//Update screen
// 	SDL_RenderPresent(mRenderer);
// }

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
				SDL_SetRenderDrawBlendMode(mRenderer, SDL_BLENDMODE_BLEND);
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
	delete mLoadingPage;
	// delete mTextRender;

	delete mGameStage;
	//Destroy window
	//SDL_DestroyRenderer(mLoadinigRenderer);
	SDL_DestroyRenderer(mRenderer);
	SDL_DestroyWindow(mWindow);
	mWindow = NULL;
	mRenderer = NULL;

	//Quit SDL subsystems
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
}

