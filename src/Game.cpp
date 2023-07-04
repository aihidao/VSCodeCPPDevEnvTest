/*This source code copyrighted by Lazy Foo' Productions 2004-2023
and may not be redistributed without written permission.*/

//Using SDL, SDL_image, standard IO, and strings
#include "Game.h"
#include <SDL_ttf.h>
#include <iostream>
#include <stdio.h>
#include <string>

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

	FC_Draw(font, mRenderer, 0, 0, "Hello, world!");
	FC_Draw(font, mRenderer, 0, 50, "你好，世界!");
	FC_Draw(font, mRenderer, 0, 150, "Hello, world%d!", frameCount);
	//Update screen
	SDL_RenderPresent(mRenderer);
}

void Game::calculateFps() {
	frameCount++;
	if(frameCount > 1000){
		frameCount = 0;
	}
	
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
		if (!loadMedias())
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

bool Game::loadMedias()
{
	//Loading success flag
	bool success = true;

	//mGameTexture = new GameTexture(mRenderer, "res/test.png");
	//if (mGameTexture == NULL)
	//{
	//	printf("Failed to load texture res/test.png!\n");
	//	success = false;
	//}
	//font = FC_CreateFont();
	//FC_LoadFont("res/font.ttf", mRenderer, "", SDL_Color(255, 255, 255, 255), TTF_STYLE_NORMAL);
	font = FC_CreateFont();
	#ifdef SDL_GPU_VERSION_MAJOR
		FC_LoadFont(font, "res/SmileySans-Oblique.ttf", 20, FC_MakeColor(0,0,0,255), TTF_STYLE_NORMAL);
	#else
		FC_LoadFont(font, mRenderer, "res/SmileySans-Oblique.ttf", 20, FC_MakeColor(255,0,0,255), TTF_STYLE_NORMAL);
	#endif
	return success;
}

void Game::close()
{
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

