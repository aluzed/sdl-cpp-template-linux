#include "SDL2/SDL.h"
#include <iostream>

int main( int argc, char* args[] ) {
	SDL_Window* pWindow = NULL;
	pWindow = SDL_CreateWindow("Test SDL2",
	SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, SDL_WINDOW_SHOWN);

	if( pWindow )
	{
		 SDL_Delay(3000);

		 SDL_DestroyWindow(pWindow);
	}
	else
	{
	 	std::cerr << "Error while creating window" << std::endl;
	}

	 SDL_Quit();

	return 0;
}
