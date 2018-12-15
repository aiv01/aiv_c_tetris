#include "tetris.h"

/* ------------------------------------- TODO ------------------------------------- */
// * Check collision when rotating tetraminos
// * Implement the correct tetramino shuffling algorithm
// * Show a preview of the net tetramino in line
// * Add sfx
// * Add music
// * TEST ALL THE THINGS *wink* *wink* Piera *wink* *wink*
// * PIERA I CHOOSE YOU
// * GOTTA TEST EM ALL
// * Optional: add animations? But just after we finish the game
// * ^ Lol seriously when?
/* -------------------------------------------------------------------------------- */

#define HORIZONTAL_CELLS 10
#define VERTICAL_CELLS 20
#define CELL_SIZE 30

int main(int argc, char **argv)
{
	int ret = 0;
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO))
	{
		SDL_Log("unable to initialize SDL2: %s", SDL_GetError());
		ret = -1;
		goto cleanup;
	}

	SDL_Window *window = SDL_CreateWindow
	(
		"tetris", 
		SDL_WINDOWPOS_UNDEFINED, 
		SDL_WINDOWPOS_UNDEFINED, 
		HORIZONTAL_CELLS * CELL_SIZE, 
		VERTICAL_CELLS * CELL_SIZE, 
		SDL_WINDOW_OPENGL
	);

	if (!window)
	{
		SDL_Log("unable to create window: %s", SDL_GetError());
		ret = -1;
		goto cleanup2;
	}
	
	SDL_Renderer *renderer = SDL_CreateRenderer(window, 0, SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED);
	if (!renderer)
	{
		SDL_Log("unable to create renderer: %s", SDL_GetError());
		ret = -1;
		goto cleanup3;
	}

	tetris_map_t map;
	tetris_map_init(&map, HORIZONTAL_CELLS, VERTICAL_CELLS);

	tetramino_t tetramino_group[TETRAMINI];
	tetramino_random_shape_init(tetramino_group, &map);

	int timer = 1000;
	Uint32 last_ticks = SDL_GetTicks();

	for (;;)
	{
		SDL_Event event;

		Uint32 current_ticks = SDL_GetTicks();
		timer -= current_ticks - last_ticks;
		last_ticks = current_ticks;

		if (timer <= 0)
		{
			if (tetramino_group_move_down(tetramino_group, &map) == TETRAMINO_DEAD)
			{
				for (int i = 0; i < TETRAMINI; i++)
				{
					if (tetramino_group[i].y == 0)
						goto cleanup4;
				}

				tetramino_random_shape_init(tetramino_group, &map);
			}
			timer = 1000;
		}

		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
			{
				goto cleanup4;
			}
			if (event.type == SDL_KEYDOWN)
			{
				if (event.key.keysym.sym == SDLK_DOWN)
				{
					if (tetramino_group_move_down(tetramino_group, &map) == TETRAMINO_DEAD)
					{
						for (int i = 0; i < TETRAMINI; i++)
						{
							if (tetramino_group[i].y == 0)
								goto cleanup4;
						}

						tetramino_random_shape_init(tetramino_group, &map);
					}
					timer = 1000;
				}
				else if (event.key.keysym.sym == SDLK_RIGHT)
				{
					tetramino_group_move_right(tetramino_group, &map);
				}
				else if (event.key.keysym.sym == SDLK_LEFT)
				{
					tetramino_group_move_left(tetramino_group, &map);
				}
				else if (event.key.keysym.sym == SDLK_UP)
				{
					tetramino_group_rotate(tetramino_group, &map);
				}
			}
		}

		// Map draw
		tetris_map_draw(&map, renderer, 30);

		// Tetramino draw
		tetramino_group_draw(tetramino_group, renderer, CELL_SIZE);

		SDL_RenderPresent(renderer);
	}
cleanup4:
	SDL_DestroyRenderer(renderer);
cleanup3:
	SDL_DestroyWindow(window);
cleanup2:
	SDL_Quit();
cleanup:
	return ret;
}
