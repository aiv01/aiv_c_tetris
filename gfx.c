#include "gfx.h"
#include "tetris.h"

static void _draw_rect_internal(SDL_Renderer *renderer, SDL_Rect *rect, int color)
{
    // Blocks colors ranges from 1-6
    // And colors ranges from 0-5 so...
    color--;

    // Innter shape
    SDL_SetRenderDrawColor(renderer, T_COLOR[color].r, T_COLOR[color].g, T_COLOR[color].b, 255);
    SDL_RenderFillRect(renderer, rect);

    // Outer border
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderDrawRect(renderer, rect);

    // Light shade
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderDrawLine(renderer, rect->x + 1, rect->y + 1, rect->x - 2 + rect->w, rect->y + 1);
    SDL_RenderDrawLine(renderer, rect->x - 2 + rect->w, rect->y + 1, rect->x - 2 + rect->w, rect->y - 2 + rect->h);
}

void field_draw(tetris_map_t *tetris_map, SDL_Renderer *renderer, int size)
{
    SDL_Rect rect;  
    rect.x = 0;
    rect.y = 0;
    rect.h = size * HEIGHT;
    rect.w = size * WIDTH;

    SDL_SetRenderDrawColor(renderer, 50, 50, 50, 127);
    SDL_RenderFillRect(renderer, &rect);
}

void tetramino_draw(TETRAMINO_T, SDL_Renderer *renderer, int size)
{
    SDL_Rect rect;
    rect.x = tetramino->x * size;
    rect.y = tetramino->y * size;
    rect.h = size;
    rect.w = size;
    _draw_rect_internal(renderer, &rect, tetramino->color_id);
}

void tetramino_group_draw(TETRAMINI_T, SDL_Renderer *renderer, int size)
{
    for (int i = 0; i < 4; i++)
        tetramino_draw(&tetramini[i], renderer, size);
}

void tetris_map_draw(TETRIS_MAP_T, SDL_Renderer *renderer, int size)
{
    field_draw(tetris_map, renderer, size);

    int y, x;
    for (y = 0; y < HEIGHT; y++)
    {
        for (x = 0; x < WIDTH; x++)
        {
            int index = WIDTH * y + x;
            if (tetris_map->cell[index] != 0)
            {
                SDL_Rect rect;
                rect.x = x * size;
                rect.y = y * size;
                rect.h = size;
                rect.w = size;
                _draw_rect_internal(renderer, &rect, tetris_map->cell[index]);
            }
        }
    }
}
