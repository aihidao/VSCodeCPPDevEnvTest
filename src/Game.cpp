/*This source code copyrighted by Lazy Foo' Productions 2004-2023
and may not be redistributed without written permission.*/

//Using SDL, SDL_image, standard IO, and strings
#include "Game.h"
#include <SDL_ttf.h>
#include <iostream>
#include <stdio.h>
#include <string>
int	Game::SCREEN_WIDTH = 800;
int	Game::SCREEN_HEIGHT = 600;

int	Game::MAP_WIDTH = 50;
int	Game::MAP_HEIGHT = 50;

int	Game::CELL_SIZE_WIDTH = 50;
int	Game::CELL_SIZE_HEIGHT = 25;
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
		while (SDL_PollEvent(&e) != 0)
		{
			//User requests quit
			if (e.type == SDL_QUIT) {
				quit = true;
			}
			else if (e.type == SDL_USEREVENT) {
				//updateDraw();
			}
			else if (e.type == SDL_MOUSEMOTION)
			{

			}
			else if (e.type == SDL_MOUSEBUTTONDOWN) {
				
			}
			else if (e.type == SDL_MOUSEBUTTONUP) {

			}
		}
		calculateFps();
		updateDraw();
	}
}

void Game::updateDraw() {
	SDL_SetRenderDrawColor(mRenderer, 0x00, 0x00, 0x00, 0xFF);
	//Clear screen
	SDL_RenderClear(mRenderer);

	mGameStage->draw();

	//mDebugInfoBox->draw();

	//Update screen
	SDL_RenderPresent(mRenderer);
}

void Game::calculateFps() {
	//frameCount++;
	// if(frameCount > 1000){
	// 	frameCount = 0;
	// }
	
}

//void Game::setTimmers() {
//	mDrawTimer = SDL_AddTimer(16, TimeEvent::drawCallback, NULL);
//}

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

bool Game::loadWidget()
{
	//Loading success flag
	bool success = true;
	//mDebugInfoBox = new DebugInfoBox(mRenderer);
	// testText = new Text("test");
	// mDebugInfoBox->push(*testText);
	//mTextRender = new TextRender(mRenderer);

	mGameStage = new GameStage(mRenderer);
	return success;
}

void Game::close()
{
	//delete mTextRender;
	//delete mDebugInfoBox;
	//delete testText;
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

