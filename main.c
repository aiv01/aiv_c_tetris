#include "tetris.h"

/* ------------------------------------- TODO ------------------------------------- */
// * Add the ability to hold one tetramino
// * Display the placement preview of the current tetramino
// * Add sfx
// * Maybe I should split tetris.c to multiple files?
// * TEST ALL THE THINGS *wink* *wink* Piera *wink* *wink*
// * PIERA I CHOOSE YOU
// * GOTTA TEST EM ALL
// * Optional: Add animations? But just after we finish the game
// * ^ Lol seriously when?
/* -------------------------------------------------------------------------------- */

int main(int argc, char **argv)
{
	int ret = 0;
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO))
	{
		SDL_Log("unable to initialize SDL2: %s", SDL_GetError());
		ret = -1;
		goto cleanup;
	}

	SDL_Window *window = SDL_CreateWindow(
		"tetris",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		(6 + HORIZONTAL_CELLS) * CELL_SIZE,
		VERTICAL_CELLS * CELL_SIZE,
		SDL_WINDOW_OPENGL);

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

	Uint8 *music_buffer = NULL;
	if (music_play(music_buffer) == -1)
	{
		ret = -1;
		goto cleanup3;
	}

	tetris_map_t map;
	tetris_map_init(&map, HORIZONTAL_CELLS, VERTICAL_CELLS);

	tetramino_t tetramino_group[TETRAMINI];
	tetramino_random_shape_init(tetramino_group, &map);

	int timer = 1000;
	Uint32 last_ticks = SDL_GetTicks();

	int instant_falling = 0;

	for (;;)
	{
		SDL_Event event;

		Uint32 current_ticks = SDL_GetTicks();
		timer -= current_ticks - last_ticks;
		last_ticks = current_ticks;

		if (timer <= 0)
		{
			if (move_down_loop(tetramino_group, &map) == TETRAMINO_DEAD)
				goto cleanup4;

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
					if (move_down_loop(tetramino_group, &map) == TETRAMINO_DEAD)
						goto cleanup4;

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
					instant_falling = 1;
					while (instant_falling == 1)
					{
						int result = move_down_loop(tetramino_group, &map);

						if (result == TETRAMINO_DEAD)
							goto cleanup4;

						if (result == 1)
							instant_falling = 0;
					}
				}
				else if (event.key.keysym.sym == SDLK_z)
				{
					tetramino_group_rotate(tetramino_group, &map, -1);
				}
				else if (event.key.keysym.sym == SDLK_x)
				{
					tetramino_group_rotate(tetramino_group, &map, 1);
				}
			}
		}

		// Map draw
		tetris_map_draw(&map, renderer);

		// Tetramino draw
		tetramino_group_draw(tetramino_group, renderer);

		// Draw previews of next pieces
		draw_next_pieces(&map, renderer);

		SDL_RenderPresent(renderer);
	}
cleanup4:
	SDL_DestroyRenderer(renderer);
cleanup3:

	SDL_DestroyWindow(window);
cleanup2:
	// SDL_FreeWAV(music_buffer); // It has issues
	SDL_Quit();
cleanup:
	return ret;
}
