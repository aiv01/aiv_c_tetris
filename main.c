#include "tetris.h"

int main(int argc, char **argv)
{
	if (SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO))
	{
		SDL_Log("unable to initialize SDL2: %s", SDL_GetError());
		return -1;
	}
	

	SDL_Quit();
	return 0;
}
