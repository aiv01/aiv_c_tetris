#include "tetris.h"

static void _draw_rect_internal(SDL_Renderer *renderer, SDL_Rect *rect, Uint8 r, Uint8 g, Uint8 b)
{
    SDL_SetRenderDrawColor(renderer, r, g, b, 255);
    SDL_RenderDrawRect(renderer, rect);
}

void tetramino_draw(tetramino_t *tetramino, SDL_Renderer *renderer, int size)
{
    SDL_Rect rect;
    rect.x = 0;
    rect.y = tetramino->y * size;
    rect.h = size;
    rect.w = size;
    _draw_rect_internal(renderer, &rect, 255, 0, 0);
}

void tetris_map_draw(tetris_map_t *map, SDL_Renderer *renderer, int size)
{
    int i;
    for (i = 0; i < map->height; i++)
    {
        if (map->cell[i] != 0)
        {
            SDL_Rect rect;
            rect.x = 0;
            rect.y = i * size;
            rect.h = size;
            rect.w = size;
            _draw_rect_internal(renderer, &rect, 255, 255, 255);
        }
    }
}