#include "tetris.h"

int main(int argc, char **argv)
{
	int ret = 0;
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO))
	{
		SDL_Log("unable to initialize SDL2: %s", SDL_GetError());
		ret = -1;
		goto cleanup;
	}

	SDL_Window *window = SDL_CreateWindow("tetris", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1024, 768, 0);
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
	tetris_map_init(&map, 10, 20);
	tetramino_t tetramino;
	tetramino_init(&tetramino, &map);

	tetramino_t tetramino_group[4];
	tetramino_cube_init(tetramino_group, &map);

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
			// if (tetramino_move_down(&tetramino, &map) == TETRAMINO_DEAD)
			if (tetramino_group_move_down(tetramino_group, &map) == TETRAMINO_DEAD)
			{
				if (tetramino.y == -1)
				{
					goto cleanup4;
				}

				// tetramino_init(&tetramino, &map);
				tetramino_cube_init(tetramino_group, &map);
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
					// if (tetramino_move_down(&tetramino, &map) == TETRAMINO_DEAD)
					if (tetramino_group_move_down(tetramino_group, &map) == TETRAMINO_DEAD)
					{
						if (tetramino.y == -1)
						{
							goto cleanup4;
						}
						// tetramino_init(&tetramino, &map);
						tetramino_cube_init(tetramino_group, &map);
					}
					timer = 1000;
				}
				else if (event.key.keysym.sym == SDLK_RIGHT)
				{
					tetramino_move_right(&tetramino, &map);
				}

				else if (event.key.keysym.sym == SDLK_LEFT)
				{
					tetramino_move_left(&tetramino, &map);
				}
			}
		}
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderClear(renderer);

		// draw map
		tetris_map_draw(&map, renderer, 30);

		//tetramino draw
		// tetramino_draw(&tetramino, renderer, 30);
		tetramino_group_draw(tetramino_group, renderer, 30);

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
