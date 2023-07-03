/*This source code copyrighted by Lazy Foo' Productions 2004-2023
and may not be redistributed without written permission.*/

//Using SDL and standard IO
#include <SDL.h>
#include <stdio.h>
#include "Game.h"

int main( int argc, char* args[] )
{
	Game* game = new Game();
	//Start up SDL and create window
	game->start();
	return 0;
}
